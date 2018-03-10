#ifndef ImageCube_MyModel_h
#define ImageCube_MyModel_h

#include "Data.h"
#include "MyConditionalPrior.h"
#include "DNest4/code/DNest4.h"
#include <ostream>

namespace ImageCube
{

// 2D arrays
using Array2D = std::vector<std::vector<double>>;

class MyModel
{
    private:

        // Static dataset
        static Data data;

        // Grids (pixel centers)
        static Array2D xs;
        static Array2D ys;
        static std::vector<double> fs;

    public:

        // Loader for the static dataset
        static void load_data(const char* filename);

    private:

        // The sources
        DNest4::RJObject<MyConditionalPrior> sources;

        // Model image
        Array3D<double> model_image;
        void compute_model_image();

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

