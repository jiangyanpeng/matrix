#pragma once

#include <iostream>
#include <string>
#include <array>
#include <algorithm>

#include "Type.hpp"

namespace ppm
{
    /// A Shape of Shape2D Base Class
    template <uint32 N>
    class Shape
    {
    public:
        /// Constructor
        /// @brief
        ///
        Shape() = default;

        /// Constructor
        /// @brief
        ///
        Shape(const std::initializer_list<uint32> &list)
        {
            std::copy_n(list.begin(), list.size(), shape.begin());
        }

        /// Deconstructor
        /// @brief
        ///
        virtual ~Shape() = default;

        /// @brief Returns whether the shape is null (constructed with the
        /// default constructor).
        /// @return bool
        ///
        virtual bool isnull() const noexcept
        {
            return shape.size() == 0 || [this]() -> bool
            {
                for (const auto &elem : shape)
                {
                    if (elem == 0)
                    {
                        return true;
                    }
                }
                return false;
            }();
        }

        /// Returns the size of the shape
        /// @brief
        /// @return size
        ///
        virtual uint32 size() const noexcept
        {
            return shape.size();
        }

        /// Returns the shape as a string representation
        /// @return std::string
        ///
        virtual std::string str() const
        {
            std::string out = "[";
            for (size_t i = 0; i < shape.size(); ++i)
            {
                out += std::to_string(shape[i]);
                if (i != (shape.size() - 1))
                {
                    out += ",";
                }
            }
            out += "]";
            return out;
        }

        /// Equality operator
        /// @brief
        /// @param InOtherShape
        /// @return bool
        ///
        bool operator==(const Shape &InOtherShape) const noexcept
        {
            bool ret = shape.size() == InOtherShape.shape();
            if (!ret)
            {
                return ret;
            }
            for (size_t i = 0; i < shape.size(); ++i)
            {
                if (shape[i] != InOtherShape.shape[i])
                {
                    return false;
                }
            }
            return true;
        }

        /// Not equality operator
        /// @brief
        /// @param InOtherShape
        /// @return bool
        ///
        bool operator!=(const Shape &InOtherShape) const noexcept
        {
            return !(*this == InOtherShape);
        }

        /// IO operator for the Shape class
        /// @param InOStream
        /// @param InShape
        /// @return std::ostream
        ///
        friend std::ostream &operator<<(std::ostream &InOStream, const Shape &InShape)
        {
            InOStream << InShape.str();
            return InOStream;
        }

    protected:
        std::array<uint32, N> shape{0};
    };

    /// A Shape2D Class for Matrix
    class Shape2D : public Shape<2>
    {
    public:
        /// Attributes
        /// @brief A Shape2D Class has rows and cols member
        /// @param rows
        /// @param cols
        ///
        uint32 rows{0};
        uint32 cols{0};

        /// Constructor
        /// @brief
        ///
        Shape2D() = default;

        /// Constructor
        /// @brief
        ///
        Shape2D(const std::initializer_list<uint32> &list)
        {
            if (list.size() == 1)
            {
                shape[0] = shape[1] = *list.begin();
            }
            else
            {
                size_t real_shape = list.size() == 0 ? 0 : 2;
                std::copy_n(list.begin(), real_shape, shape.begin());
            }
        }

        /// Constructor
        /// @param InSquareSize
        ///
        explicit Shape2D(uint32 InSquareSize) noexcept : rows(InSquareSize),
                                                         cols(InSquareSize)
        {
            shape[0] = InSquareSize, shape[1] = InSquareSize;
        }

        /// Constructor
        /// @param InRows
        /// @param InCols
        ///
        Shape2D(uint32 InRows, uint32 InCols) noexcept : rows(InRows),
                                                         cols(InCols)
        {
            shape[0] = InRows, shape[1] = InCols;
        }

        /// Equality operator
        /// @brief
        /// @param InOtherShape
        /// @return bool
        ///
        bool operator==(const Shape2D &InOtherShape) const noexcept
        {
            return rows == InOtherShape.rows && cols == InOtherShape.cols;
        }

        /// Not equality operator
        /// @brief
        /// @param InOtherShape
        /// @return bool
        ///
        bool operator!=(const Shape2D &InOtherShape) const noexcept
        {
            return !(*this == InOtherShape);
        }

        /// Returns whether the shape is square or not.
        /// @return bool
        ///
        bool issquare() const noexcept
        {
            return rows == cols;
        }

        /// IO operator for the Shape2D class
        /// @param InOStream
        /// @param InShape
        /// @return std::ostream
        ///
        friend std::ostream &operator<<(std::ostream &InOStream, const Shape2D &InShape)
        {
            InOStream << InShape.str();
            return InOStream;
        }
    };
} // namespace ppm
