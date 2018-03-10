#include "MyConditionalPrior.h"
#include "DNest4/code/DNest4.h"
#include <cmath>

namespace ImageCube
{

MyConditionalPrior::MyConditionalPrior()
{

}

void MyConditionalPrior::from_prior(DNest4::RNG& rng)
{

}

double MyConditionalPrior::perturb_hyperparameters(DNest4::RNG& rng)
{
    double logH = 0.0;

    return logH;
}


// vec = { xc, yc, fc, mass, width, q, theta, fwidth }
double MyConditionalPrior::log_pdf(const std::vector<double>& vec) const
{q
    return 0.0;
}

void MyConditionalPrior::from_uniform(std::vector<double>& vec) const
{
    vec[0] = x_min + (x_max - x_min)*vec[0];
    vec[1] = y_min + (y_max - y_min)*vec[1];
    vec[2] = f_min + (f_max - f_min)*vec[2];


}

void MyConditionalPrior::to_uniform(std::vector<double>& vec) const
{

}

void MyConditionalPrior::print(std::ostream& out) const
{
    out << ' ';
}

} // namespace ImageCube

