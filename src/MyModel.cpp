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
{

}

void MyModel::from_prior(DNest4::RNG& rng)
{

}

double MyModel::perturb(DNest4::RNG& rng)
{
    double logH = 0.0;
    return logH;
}

double MyModel::log_likelihood() const
{
    double logL = 0.0;
    return logL;
}

void MyModel::print(std::ostream& out) const
{

}

std::string MyModel::description() const
{
    return std::string("");
}

} // namespace ImageCube

