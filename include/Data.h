#ifndef ImageCube_Data_h
#define ImageCube_Data_h

#include <cstdlib>
#include <vector>

namespace ImageCube
{

// For 3D arrays
template<typename T>
using Array3D = std::vector<std::vector<std::vector<T>>>;

class Data
{
    private:

        // Hard-coded metadata for now
        static constexpr size_t nx = 75;
        static constexpr size_t ny = 80;
        static constexpr size_t nf = 100;

        // The data itself
        Array3D<double> pixel_intensities;

    public:

        // Constructor
        Data();

        // Constructor that also loads data
        Data(const char* filename);

        // Load data from file
        void load(const char* filename);

        // Getter
        const Array3D<double> get_pixel_intensities() const
        { return pixel_intensities; }

};

} // namespace ImageCube

#endif

