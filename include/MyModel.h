#ifndef ImageCube_MyModel_h
#define ImageCube_MyModel_h

#include "Data.h"
#include "DNest4/code/DNest4.h"
#include <ostream>

namespace ImageCube
{

class MyModel
{
    private:

        // Static dataset
        static Data data;

    public:

        // Loader for the static dataset
        static void load_data(const char* filename);

    private:

    public:
        // Constructor only gives size of params
        MyModel();

        // Generate the point from the prior
        void from_prior(DNest4::RNG& rng);

        // Metropolis-Hastings proposals
        double perturb(DNest4::RNG& rng);

        // Likelihood function
        double log_likelihood() const;

        // Print to stream
        void print(std::ostream& out) const;

        // Return string with column information
        std::string description() const;
};

} // namespace ImageCube

#endif

