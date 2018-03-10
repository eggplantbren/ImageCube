#include "MyConditionalPrior.h"
#include "Data.h"
#include "DNest4/code/DNest4.h"
#include <cmath>

namespace ImageCube
{

MyConditionalPrior::MyConditionalPrior()
:cauchy(0.0, 5.0)
{

}

void MyConditionalPrior::from_prior(DNest4::RNG& rng)
{
    while(true)
    {
        mass_scale = cauchy.generate(rng);
        if(std::abs(mass_scale) <= 300.0)
            break;
    }
    mass_scale = exp(mass_scale);
}

double MyConditionalPrior::perturb_hyperparameters(DNest4::RNG& rng)
{
    double logH = 0.0;

    mass_scale = log(mass_scale);
    logH += cauchy.perturb(mass_scale, rng);
    if(std::abs(mass_scale) > 300.0)
        return -1E300;
    mass_scale = exp(mass_scale);

    return logH;
}


// vec = { xc, yc, fc, mass, width, q, theta, fwidth }
double MyConditionalPrior::log_pdf(const std::vector<double>& vec) const
{
    double logp = 0.0;

    if(vec[3] < 0.0)
        return -1E300;
    logp += -log(mass_scale) - vec[3]/mass_scale;

    return 0.0;
}

void MyConditionalPrior::from_uniform(std::vector<double>& vec) const
{
    vec[0] = Data::x_min + (Data::x_max - Data::x_min)*vec[0];
    vec[1] = Data::y_min + (Data::y_max - Data::y_min)*vec[1];
    vec[2] = Data::f_min + (Data::f_max - Data::f_min)*vec[2];
    vec[3] = -mass_scale*log(1.0 - vec[3]);
    vec[4] = 10.0*vec[4];
    vec[5] = M_PI*vec[5];
    vec[6] = 10.0*vec[6];
    vec[7] = 200.0*vec[7];
}

void MyConditionalPrior::to_uniform(std::vector<double>& vec) const
{
    vec[0] = (vec[0] - Data::x_min)/(Data::x_max - Data::x_min);
    vec[1] = (vec[1] - Data::y_min)/(Data::y_max - Data::y_min);
    vec[2] = (vec[2] - Data::f_min)/(Data::f_max - Data::f_min);
    vec[3] = 1.0 - exp(-vec[3]/mass_scale);
    vec[4] = vec[4] / 10.0;
    vec[5] = vec[5] / M_PI;
    vec[6] = vec[6] / 10.0;
    vec[7] = vec[7] / 200.0;
}

void MyConditionalPrior::print(std::ostream& out) const
{
    out << mass_scale << ' ';
}

} // namespace ImageCube

