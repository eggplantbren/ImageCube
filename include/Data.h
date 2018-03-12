#ifndef ImageCube_Data_h
#define ImageCube_Data_h

#include <cmath>
#include <cstdlib>
#include <vector>

namespace ImageCube
{

// For 3D arrays
template<typename T>
using Array3D = std::vector<std::vector<std::vector<T>>>;

class Data
{
    public:

        // Hard-coded metadata for now
        static constexpr size_t nx = 75;
        static constexpr size_t ny = 80;
        static constexpr size_t nf = 100;
        static constexpr double dx = 0.1;
        static constexpr double dy = 0.1;
        static constexpr double df = 1.0;
        static constexpr double x_min = 0.0;
        static constexpr double x_max = nx*dx;
        static constexpr double y_min = 0.0;
        static constexpr double y_max = ny*dy;
        static constexpr double scale = sqrt((x_max - x_min)*(y_max - y_min));
        static constexpr double f_min = 0.0;
        static constexpr double f_max = nf*df;
        static constexpr double sigma = 1E-3;

    private:

        // The data itself
        Array3D<double> image;

    public:

        // Constructor
        Data();

        // Constructor that also loads data
        Data(const char* filename);

        // Load data from file
        void load(const char* filename);

        // Getter
        const Array3D<double> get_image() const
        { return image; }

};

} // namespace ImageCube

#endif

