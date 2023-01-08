#include <iostream>

#include "Log.h"
#include "matrix/Shape.hpp"

int main()
{
    LOG_INFO("Shape Test");
    LOG_INFO("shapend: %s", ppm::Shape<4>({1, 2, 3, 4}).str().c_str());

    LOG_INFO("shape2d empty: %i", ppm::Shape2D({}).isnull());
    LOG_INFO("shape2d: %s", ppm::Shape2D({}).str().c_str());
    LOG_INFO("shape2d: %s", ppm::Shape2D({1, 2}).str().c_str());
    LOG_INFO("shape2d: %s", ppm::Shape2D({3, 4, 5}).str().c_str());
    return 0;
}