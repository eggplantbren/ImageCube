#include "Data.h"
#include <fstream>
#include <iostream>

namespace ImageCube
{

Data::Data()
{
    // Allocate space in the array
    image.resize(nx);
    for(size_t i=0; i<image.size(); ++i)
    {
        image[i].resize(ny);
        for(size_t j=0; j<image[i].size(); ++j)
            image[i][j].resize(nf);
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

    // Message
    std::cout << "# Reading data from " << filename << "..." << std::flush;

    // Read the data
    for(size_t i=0; i<nx; ++i)
        for(size_t j=0; j<ny; ++j)
            for(size_t k=0; k<nf; ++k)
                fin >> image[i][j][k];

    // Close the file
    fin.close();
    std::cout << "done." << std::endl;
}

} // namespace ImageCube

