#ifndef __PPM_MATRIX_H__
#define __PPM_MATRIX_H__

#include <array>
#include <cmath>
#include <deque>
#include <forward_list>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <numeric>
#include <set>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <iomanip>

#include "Log.h"
#include "Type.hpp"
#include "Shape.hpp"

namespace ppm
{
    /// A MatrixBase of Matrix2D Base Class
    template <typename DType, size_t R, size_t C, std::size_t A = MT(R, C)>
    class MatrixBase;

    /// A MatrixBase of Matrix2D Base Class
    template <typename DType, std::size_t R, std::size_t C>
    class MatrixBase<DType, R, C, 1>
    {
    protected:
        /// Constructor
        /// @brief
        ///
        MatrixBase() : data_{} {}

        /// Constructor
        /// @brief
        ///
        template <size_t L, enable_arithmetic_type_t<DType> * = nullptr>
        MatrixBase(const std::array<DType, L> &list) : data_{}
        {
            constexpr auto real_idx = Less(L, R * C);
            std::copy_n(list.begin(), real_idx, data_.begin());
        }

        /// Constructor
        /// @brief
        ///
        template <enable_arithmetic_type_t<DType> * = nullptr>
        MatrixBase(const std::initializer_list<DType> &list) : data_{}
        {
            auto real_idx = list.size() < R * C ? list.size() : R * C;
            std::copy_n(list.begin(), real_idx, data_.begin());
        }

        /// Constructor
        /// @brief
        ///
        template <enable_arithmetic_type_t<DType> * = nullptr>
        MatrixBase(const std::vector<DType> &list) : data_{}
        {
            auto real_idx = list.size() < R * C ? list.size() : R * C;
            std::copy_n(list.begin(), real_idx, data_.begin());
        }

    protected:
        std::array<DType, R * C> data_;
    };

    /// A MatrixBase of Matrix2D Base Class
    template <typename DType, std::size_t R, std::size_t C>
    class MatrixBase<DType, R, C, 0>
    {
    private:
        using Allocator = std::allocator<DType>;
        using AllocType = typename std::allocator_traits<Allocator>::template rebind_alloc<DType>;
        using AllocTraits = std::allocator_traits<AllocType>;

    public:
        using value_type = DType;
        using allocator_type = Allocator;
        using pointer = typename AllocTraits::pointer;
        using const_pointer = typename AllocTraits::const_pointer;
        using reference = DType &;
        using const_reference = const DType &;
        using size_type = uint32;
        using difference_type = typename AllocTraits::difference_type;

    protected:
        /// Constructor
        /// @brief
        ///
        MatrixBase() : data_(R * C, 0.0) {}

        /// Constructor
        /// @brief
        ///
        template <size_t L, enable_arithmetic_type_t<DType> * = nullptr>
        MatrixBase(const std::array<DType, L> &list) : data_(R * C, 0.0)
        {
            constexpr auto real_idx = Less(L, R * C);
            std::copy_n(list.begin(), real_idx, data_.begin());
        }

        /// Constructor
        /// @brief
        ///
        template <enable_arithmetic_type_t<DType> * = nullptr>
        MatrixBase(const std::initializer_list<DType> &list) : data_(R * C, 0.0)
        {
            auto real_idx = list.size() < R * C ? list.size() : R * C;
            std::copy_n(list.begin(), real_idx, data_.begin());
        }

        /// Constructor
        /// @brief
        ///
        template <enable_arithmetic_type_t<DType> * = nullptr>
        MatrixBase(const std::vector<DType> &list) : data_(R * C, 0.0)
        {
            auto real_idx = list.size() < R * C ? list.size() : R * C;
            std::copy_n(list.begin(), real_idx, data_.begin());
        }

    protected:
        std::vector<DType> data_;

        allocator_type allocator_{};
        pointer array_{nullptr};
        bool owns_ptr_{false};
    };

    // Class Description:
    /// Holds 1D and 2D arrays, the main work horse of the Matrix library
    template <typename DType, std::size_t R, std::size_t C>
    class Matrix2D : public MatrixBase<DType, R, C>
    {
    public:
        template <size_t A, typename RT = void>
        using enable_squre_matrix_t = typename std::enable_if<A == C, RT>::type;

    public:
        /// Constructor
        /// @brief
        ///
        Matrix2D() = default;

        /// Member Functions
        /// @brief
        ///
        DType *data()
        {
            return &(this->data_[0]);
        }

        /// Member Functions
        /// @brief
        ///
        const DType *data() const
        {
            return &(this->data_[0]);
        }

        /// Member Functions
        /// @brief
        ///
        constexpr size_t rows() const
        {
            shape_.rows;
        }

        /// Member Functions
        /// @brief
        ///
        constexpr size_t cols() const
        {
            shape_.cols;
        }

        /// Member Functions
        /// @brief
        ///
        constexpr size_t size()
        {
            return R * C;
        }

        /// Member Functions
        /// @brief
        ///
        Matrix2D<DType, 1, C> row(size_t idx) const
        {
            Matrix2D<DType, 1, C> result{};
            if (idx >= R)
            {
                LOG_ERROR("[Index Out Of Range Rows <%ivs%i>]", ++idx, R);
                result.fill(details::nan);
                return result;
            }
            for (size_t i = 0; i < C; ++i)
            {
                result[i] = this->data_[idx * C + i];
            }
            return result;
        }

        /// Member Functions
        /// @brief
        ///
        Matrix2D<DType, R, 1> col(size_t idx) const
        {
            Matrix2D<DType, R, 1> result{};
            if (idx >= C)
            {
                LOG_ERROR("[Index Out Of Range Cols <%ivs%i>]", ++idx, C);
                result.fill(details::nan);
                return result;
            }
            for (size_t i = 0; i < R; ++i)
            {
                result[i] = this->data_[i * C + idx];
            }
            return result;
        }

        /// Member Functions
        /// @brief
        ///
        void fill(DType val)
        {
            std::fill(this->data_.begin(), this->data_.end(), val);
        }

        /// Method Description:
        /// overload operator () and []
        ///
        DType operator()(size_t row, size_t col)
        {
            if (row >= R)
            {
                LOG_ERROR("%i Out Range Matrix2D<%i,%i>.", row, R, C);
                return details::nan;
            }
            if (col >= C)
            {
                LOG_ERROR("%i Out Range Matrix2D<%i,%i>.", col, R, C);
                return details::nan;
            }
            return this->data_[row + col * R];
        }
        const DType operator()(size_t row, size_t col) const
        {
            if (row >= R)
            {
                LOG_ERROR("%i Out Range Matrix2D<%i,%i>.", row, R, C);
                return details::nan;
            }
            if (col >= C)
            {
                LOG_ERROR("%i Out Range Matrix2D<%i,%i>.", col, R, C);
                return details::nan;
            }
            return this->data_[row + col * R];
        }
        DType operator()(const std::pair<size_t, size_t> &idx)
        {
            return this->data_[idx.first + idx.second * R];
        }
        const DType operator()(const std::pair<size_t, size_t> &idx) const
        {
            return this->data_[idx.first + idx.second * R];
        }
        DType &operator[](size_t idx)
        {
            return this->data_[idx];
        }
        DType &operator[](const std::pair<size_t, size_t> &idx)
        {
            return this->data_[idx.first + idx.second * R];
        }

        /// Returns the shape as a string representation
        /// @return std::string
        ///
        std::string str() const
        {
            std::stringstream ss;
            ss << "Matrix2D<" << R << "," << C << ">:\n";
            for (size_t i = 0; i < R; i++)
            {
                for (size_t j = 0; j < C; j++)
                {
                    ss << std::setw(12) << (*this)(i, j) << "\t";
                }
                if (i != R - 1)
                {
                    ss << "\n";
                }
            }
            return ss.str();
        }

        /// IO operator for the Shape2D class
        /// @param InOStream
        /// @param InShape
        /// @return std::ostream
        ///
        friend std::ostream &operator<<(std::ostream &InOStream, const Matrix2D &InMatrix)
        {
            InOStream << InMatrix.str();
            return InOStream;
        }

        /// Static Function Description:
        /// @brief
        ///
        static Matrix2D eye()
        {
            Matrix2D<DType, R, C> result{};
            size_t real_idx = R < C ? R : C;
            for (size_t i = 0; i < real_idx; ++i)
            {
                result[i * (R + 1)] = 1.0;
            }
            return result;
        }

        /// Static Function Description:
        /// @brief
        ///
        static Matrix2D zero()
        {
            Matrix2D<DType, R, C> result{};
            result.fill(0.0);
            return result;
        }

        /// Static Function Description:
        /// @brief
        ///
        template <size_t L = Less(R, C)>
        static enable_arithmetic_type_t<DType, Matrix2D<DType, L, L>> diag(const std::initializer_list<DType> &list)
        {
            Matrix2D<DType, L, L> result{};
            size_t idx = 0u;
            for (auto iter = list.begin(); iter != list.end(); iter++)
            {
                result[{idx, idx}] = *iter;
                ++idx;
            }
            return result;
        }

        template <size_t L>
        static Matrix2D<DType, L, L> diag(const Matrix2D<DType, L, 1> &list)
        {
            Matrix2D<DType, L, L> result{};
            for (size_t i = 0; i < C; i++)
            {
                result(i, i) = list[i];
            }
            return result;
        }
        template <size_t L>
        static Matrix2D<DType, L, L> diag(const Matrix2D<DType, 1, L> &list)
        {
            Matrix2D<DType, L, L> result{};
            for (size_t i = 0; i < C; i++)
            {
                result(i, i) = list[i];
            }
            return result;
        }

        template <size_t A = R>
        enable_squre_matrix_t<A, DType> trace() const
        {
            DType res = 0.0;
            for (size_t i = 0; i < A; i++)
            {
                res += (*this)(i, i);
            }
            return res;
        }

    private:
        //====================================Attributes==============================
        Shape<2> shape_{R, C};
    };
} // namespace ppm
#endif //__PPM_MATRIX_H__
