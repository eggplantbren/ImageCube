#include "MyModel.h"
#include "DNest4/code/DNest4.h"

namespace ImageCube
{

// The data
Data MyModel::data;

void MyModel::load_data(const char* filename)
{
    data.load(filename);
}

MyModel::MyModel()
:sources(8,
         100,
         false,
         MyConditionalPrior(), DNest4::PriorType::log_uniform)
,model_pixel_intensities(data.get_pixel_intensities())
{

}

void MyModel::compute_model_pixel_intensities()
{
    // Grab the source parameters
    const auto& components = sources.get_components();
    size_t num_components = components.size();

    // Rearrange them
    std::vector<double> xc, yc, fc, mass, width, q, cos_theta, sin_theta,
                        fwidth, coeff;
    for(const auto& component: components)
    {
        xc.push_back(component[0]);
        yc.push_back(component[1]);
        fc.push_back(component[2]);
        mass.push_back(component[3]);
        width.push_back(component[4]);
        q.push_back(component[5]);
        cos_theta.push_back(cos(component[6]));
        sin_theta.push_back(sin(component[6]));
        fwidth.push_back(component[7]);
    }
    for(size_t c=0; c<num_components; ++c)
    {
        coeff.push_back(mass[c]/(2.0*M_PI*width[c]*width[c]));
        
    }


    double x, y, f, xx, yy;
    for(size_t i=0; i<Data::nx; ++i)
    {
        x = Data::x_min + 0.5*Data::dx;
        for(size_t j=0; j<Data::ny; ++j)
        {
            y = Data::y_min + 0.5*Data::dy;
            for(size_t k=0; k<Data::nf; ++k)
            {
                f = Data::f_min + 0.5*Data::df;

                // Shorthand
                double& pixel = model_pixel_intensities[i][j][k];
                pixel = 0.0;

                for(size_t c=0; c<num_components; ++c)
                {
                    //pixel += 
                }
            }
        }
    }
}

void MyModel::from_prior(DNest4::RNG& rng)
{
    sources.from_prior(rng);
}

double MyModel::perturb(DNest4::RNG& rng)
{
    double logH = 0.0;

    logH += sources.perturb(rng);

    return logH;
}

double MyModel::log_likelihood() const
{
    double logL = 0.0;
    return logL;
}

void MyModel::print(std::ostream& out) const
{
    sources.print(out);
}

std::string MyModel::description() const
{
    return std::string("");
}

} // namespace ImageCube

