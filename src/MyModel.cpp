#include "MyModel.h"
#include "DNest4/code/DNest4.h"

namespace ImageCube
{

// The data
Data MyModel::data;
Array2D MyModel::xs;
Array2D MyModel::ys;
std::vector<double> MyModel::fs;

void MyModel::load_data(const char* filename)
{
    // Read in data
    data.load(filename);

    // Set up grids
    xs.resize(Data::nx, std::vector<double>(Data::ny));
    ys.resize(Data::nx, std::vector<double>(Data::ny));
    fs.resize(Data::nf);

    for(size_t i=0; i<Data::nx; ++i)
    {
        for(size_t j=0; j<Data::ny; ++j)
        {
            xs[i][j] = Data::x_min + (i + 0.5)*Data::dx;
            ys[i][j] = Data::y_min + (j + 0.5)*Data::dy;
        }
    }

    for(size_t k=0; k<Data::nf; ++k)
        fs[k] = Data::f_min + (k + 0.5)*Data::df;
}

MyModel::MyModel()
:sources(8,
         20,
         false,
         MyConditionalPrior(), DNest4::PriorType::log_uniform)
,model_image(data.get_image())
{

}


void MyModel::compute_model_image(bool update)
{
    // Grab the source parameters
    const auto& components = (update)?(sources.get_added()):
                             (sources.get_components());

    // Zero the image
    if(!update)
    {
        for(size_t i=0; i<Data::nx; ++i)
            for(size_t j=0; j<Data::ny; ++j)
                for(size_t k=0; k<Data::nf; ++k)
                    model_image[i][j][k] = 0.0;
    }

    for(const auto& component: components)
    {
        // component = { xc, yc, fc, mass, width, q, theta, fwidth }

        // Create rotated and translated grid
        double q = component[5];
        double inv_q = 1.0/q;
        double cos_theta = cos(component[6]);
        double sin_theta = sin(component[6]);
        double coeff = component[3]/(2*M_PI*pow(component[4], 2));
        double tau = pow(component[4], -2);
        auto xx = xs;
        auto yy = ys;
        for(size_t i=0; i<Data::nx; ++i)
        {
            for(size_t j=0; j<Data::ny; ++j)
            {
                xx[i][j] = cos_theta*(xs[i][j] - component[0])
                                + sin_theta*(ys[i][j] - component[1]);
                yy[i][j] = -sin_theta*(xs[i][j] - component[0])
                                + cos_theta*(ys[i][j] - component[1]);
            }
        }

        std::vector<double> f_gaussian(Data::nf);
        for(size_t k=0; k<Data::nf; ++k)
            f_gaussian[k] = exp(-0.5*pow((fs[k] - component[2])/component[7], 2))
                                           /sqrt(2*M_PI*component[7]);

        double rsq;
        for(size_t i=0; i<Data::nx; ++i)
        {
            for(size_t j=0; j<Data::ny; ++j)
            {
                // (r/width)^2
                rsq = (q*pow(xx[i][j], 2) + inv_q*pow(yy[i][j], 2)) * tau;

                if(rsq <= 100.0)
                {
                    for(size_t k=0; k<Data::nf; ++k)
                    {
                        model_image[i][j][k] +=
                                coeff*exp(-0.5*rsq)*f_gaussian[k];
                    }
                }
            }
        }
    }
}


void MyModel::from_prior(DNest4::RNG& rng)
{
    sources.from_prior(rng);
    compute_model_image();
}

double MyModel::perturb(DNest4::RNG& rng)
{
    double logH = 0.0;

    logH += sources.perturb(rng);
    compute_model_image(sources.get_removed().size() == 0);

    return logH;
}

double MyModel::log_likelihood() const
{
    double logL = 0.0;

    double C = -log(Data::sigma) - 0.5*log(2*M_PI);
    double tau = pow(Data::sigma, -2);
    const auto& d = data.get_image();

    for(size_t i=0; i<Data::nx; ++i)
        for(size_t j=0; j<Data::ny; ++j)
            for(size_t k=0; k<Data::nf; ++k)
                logL += C - 0.5*tau*pow(d[i][j][k] - model_image[i][j][k], 2);

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

