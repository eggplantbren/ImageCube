#ifndef ImageCube_MyConditionalPrior_h
#define ImageCube_MyConditionalPrior_h

#include "DNest4/code/DNest4.h"

namespace ImageCube
{

class MyConditionalPrior : public DNest4::ConditionalPrior
{
    private:

        // Scale parameter for masses
        double mass_scale;

        // Hyperparameters for widths
        double mu_width, sig_width;

        // A Cauchy distribution
        DNest4::Cauchy cauchy;

        double perturb_hyperparameters(DNest4::RNG& rng);

    public:
        MyConditionalPrior();

        void from_prior(DNest4::RNG& rng);

        double log_pdf(const std::vector<double>& vec) const;
        void from_uniform(std::vector<double>& vec) const;
        void to_uniform(std::vector<double>& vec) const;

        void print(std::ostream& out) const;
        static const int weight_parameter = 1;
};

} // namespace ImageCube

#endif

