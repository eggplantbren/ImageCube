#include <iostream>
#include "DNest4/code/DNest4.h"
#include "MyModel.h"

using namespace ImageCube;

int main(int argc, char** argv)
{
    // Load the data
    MyModel::load_data("data/example_data.txt");

    // Run the sampler
    DNest4::start<MyModel>(argc, argv);

    return 0;
}

