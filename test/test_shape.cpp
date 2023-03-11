#include <iostream>

#include "Log.h"
#include "Shape.hpp"

int main()
{
    LOG_INFO("Shape Test");
    LOG_INFO("shapend: %s", ppm::Shape<3>({1, 2, 3, 4}).str().c_str());
    return 0;
}