#include "Data.h"
#include <fstream>
#include <iostream>

namespace ImageCube
{

Data::Data()
{
    // Allocate space in the array
    pixel_intensities.resize(nx);
    for(size_t i=0; i<pixel_intensities.size(); ++i)
    {
        pixel_intensities[i].resize(ny);
        for(size_t j=0; j<pixel_intensities[i].size(); ++j)
            pixel_intensities[i][j].resize(nf);
    }
}

Data::Data(const char* filename)
:Data()
{
    load(filename);
}

void Data::load(const char* filename)
{
    // Open the file
    std::fstream fin(filename, std::ios::in);
    if(!fin)
    {
        std::cerr << "Couldn't open file " << filename << '.' << std::endl;
        return;
    }

    // Read the data
    for(size_t i=0; i<nx; ++i)
        for(size_t j=0; j<ny; ++j)
            for(size_t k=0; k<nf; ++k)
                fin >> pixel_intensities[i][j][k];

    // Close the file
    fin.close();
}

} // namespace ImageCube

