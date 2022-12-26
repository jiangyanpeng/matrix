#ifndef PPM_MATRIX_H_
#define PPM_MATRIX_H_

#include <string>
#include <array>

namespace ppm
{
    // Max matrix rows ans cols. such as more then limit_matrix_size memory will use heap, otherwise use stash
    constexpr size_t limit_matrix_size = 260;
    constexpr size_t is_limit_size(size_t rows, size_t cols)
    {
        return rows * cols < limit_matrix_size ? 1 : 0;
    }

    template <size_t M, size_t N, size_t A = is_limit_size(M, N)>
    class MatrixBase;

    template <size_t M, size_t N>
    class MatrixBase<M, N, 1>
    {
    public:
        MatrixBase() : data_({}) {}

    protected:
        std::array<double, M * N> data_;
    };

    template <size_t M, size_t N>
    class MatrixBase<M, N, 0>
    {
    };
}

#endif