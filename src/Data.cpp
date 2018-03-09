#include "Data.h"

namespace ImageCube
{

Data::Data()
{
    // Allocate space in the array
    pixel_intensities.resize(nx);
    for(size_t i=0; i<pixel_intensities.size(); ++i)
    {
        pixel_intensities[i].resize(ny);
        for(size_t j=0; j<pixel_intensities.size(); ++j)
            pixel_intensities[i][j].resize(nf);
    }
}

} // namespace ImageCube

