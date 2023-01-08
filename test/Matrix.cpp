#include <iostream>

#include "Log.h"
#include "matrix/Matrix.h"

int main()
{
    LOG_INFO("Matrix Test");

    auto matrix = ppm::Matrix2D<double, 4, 4>::eye();
    std::cout << ppm::Matrix2D<double, 4, 4>::diag({1, 2, 3, 4}) << std::endl;

    std::cout << matrix << std::endl;
    std::cout << matrix.row(4) << std::endl;
    std::cout << matrix.col(3) << std::endl;

    std::cout << "trace: " << matrix.trace() << " size: " << matrix.size() << std::endl;
    return 0;
}