#pragma once

#include <iostream>
#include <string>
#include <array>
#include <algorithm>

#include "Type.hpp"

namespace ppm
{
    /// A Shape of Shape Base Class
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
            std::copy_n(list.begin(), list.size(), shape_.begin());
        }

        /// Constructor
        /// @brief
        ///
        Shape(const Shape<N> &shape)
        {
            for (size_t i = 0; i < static_cast<size_t>(N); ++i)
            {
                shape_[i] = shape.shape_[i];
            }
        }

        /// Deconstructor
        /// @brief
        ///
        ~Shape() = default;

        /// @brief Returns whether the shape_ is null (constructed with the
        /// default constructor).
        /// @return bool
        ///
        bool isnull() const noexcept
        {
            return shape_.size() == 0 || [this]() -> bool
            {
                for (const auto &elem : shape_)
                {
                    if (elem == 0)
                    {
                        return true;
                    }
                }
                return false;
            }();
        }

        /// Returns the size of the shape_
        /// @brief
        /// @return size
        ///
        uint32 size() const noexcept
        {
            uint32 ret = 0;
            for (size_t i = 0; i < shape_.size(); ++i)
            {
                ret += shape_[i];
            }
            return ret;
        }

        /// Returns the dims of the shape_
        /// @brief
        /// @return size
        ///
        uint32 dims(size_t index) const noexcept
        {
            if (index >= shape_.size())
            {
                LOG_DEBUG("index(%i) out of range.", index);
                return -1;
            }
            return shape_[index];
        }

        /// Returns the shape_ as a string representation
        /// @return std::string
        ///
        virtual std::string str() const
        {
            std::string out = "[";
            for (size_t i = 0; i < shape_.size(); ++i)
            {
                out += std::to_string(shape_[i]);
                if (i != (shape_.size() - 1))
                {
                    out += ",";
                }
            }
            out += "]";
            return out;
        }

        /// operator =
        /// @brief
        /// @param input
        /// @return Shape
        ///
        Shape<N> &operator=(const Shape<N> &input)
        {
            for (size_t i = 0; i < static_cast<size_t>(N); ++i)
            {
                shape_[i] = input.shape_[i];
            }
            return *this;
        }

        /// Equality operator
        /// @brief
        /// @param InOtherShape
        /// @return bool
        ///
        bool operator==(const Shape &InOtherShape) const noexcept
        {
            bool ret = shape_.size() == InOtherShape.shape_();
            if (!ret)
            {
                return ret;
            }
            for (size_t i = 0; i < shape_.size(); ++i)
            {
                if (shape_[i] != InOtherShape.shape_[i])
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

    private:
        std::array<uint32, N> shape_{0};
    };

    /// A Shape Class for Matrix
    template <>
    class Shape<2>
    {
    public:
        /// Attributes
        /// @brief A Shape Class has rows and cols member
        /// @param rows
        /// @param cols
        ///
        uint32 rows{0};
        uint32 cols{0};

        /// Constructor
        /// @brief
        ///
        Shape() = default;

        /// Constructor
        /// @brief
        ///
        Shape(const std::initializer_list<uint32> &list)
        {
            if (list.size() == 1)
            {
                shape_[0] = shape_[1] = *list.begin();
            }
            else
            {
                size_t real_shape_ = list.size() == 0 ? 0 : 2;
                std::copy_n(list.begin(), real_shape_, shape_.begin());
            }
            rows = shape_[0];
            cols = shape_[1];
        }

        /// Constructor
        /// @brief
        ///
        Shape(const Shape<2> &shape)
        {
            shape_[0] = shape.shape_[0];
            shape_[1] = shape.shape_[1];
            rows = shape_[0];
            cols = shape_[1];
        }

        /// Constructor
        /// @param InSquareSize
        ///
        explicit Shape(uint32 InSquareSize) noexcept : rows(InSquareSize),
                                                       cols(InSquareSize)
        {
            shape_[0] = InSquareSize, shape_[1] = InSquareSize;
        }

        /// Constructor
        /// @param InRows
        /// @param InCols
        ///
        Shape(uint32 InRows, uint32 InCols) noexcept : rows(InRows),
                                                       cols(InCols)
        {
            shape_[0] = InRows, shape_[1] = InCols;
        }

        /// Returns the size of the shape_
        /// @brief
        /// @return size
        ///
        uint32 dims(size_t index) const noexcept
        {
            if (index >= shape_.size())
            {
                LOG_ERROR("index(%i) out of range.", index);
                return -1;
            }
            return shape_[index];
        }

        /// Returns the size of the shape_
        /// @brief
        /// @return size
        ///
        virtual uint32 size() const noexcept
        {
            return shape_[0] + shape_[1];
        }

        /// Returns the shape_ as a string representation
        /// @return std::string
        ///
        virtual std::string str() const
        {
            std::string out = "[";
            for (size_t i = 0; i < shape_.size(); ++i)
            {
                out += std::to_string(shape_[i]);
                if (i != (shape_.size() - 1))
                {
                    out += ",";
                }
            }
            out += "]";
            return out;
        }

        /// operator =
        /// @brief
        /// @param input
        /// @return Shape
        ///
        Shape<2> &operator=(const Shape<2> &input)
        {
            shape_[0] = input.shape_[0];
            shape_[1] = input.shape_[1];
            rows = shape_[0];
            cols = shape_[1];
            return *this;
        }

        /// Equality operator
        /// @brief
        /// @param InOtherShape
        /// @return bool
        ///
        bool operator==(const Shape &InOtherShape) const noexcept
        {
            return rows == InOtherShape.rows && cols == InOtherShape.cols;
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

        /// Returns whether the shape_ is square or not.
        /// @return bool
        ///
        bool issquare() const noexcept
        {
            return rows == cols;
        }

    private:
        std::array<uint32, 2> shape_{0};
    };

    /// A Shape Class for Tensor
    template <>
    class Shape<4>
    {
    public:
        /// Attributes
        /// @brief A Shape Class has num, channel, width, height
        /// @param num     [N]
        /// @param channel [C]
        /// @param height  [H]
        /// @param width   [W]
        ///
        uint32 num;
        uint32 channel;
        uint32 height;
        uint32 width;

        /// Constructor
        /// @brief
        ///
        Shape() = default;

        /// Constructor
        /// @brief
        ///
        Shape(const std::initializer_list<uint32> &list)
        {
            if (list.size() == 1)
            {
                shape_[0] = shape_[1] = shape_[2] = shape_[4] = *list.begin();
            }
            else
            {
                size_t real_shape_ = list.size() == 0 ? 0 : 4;
                std::copy_n(list.begin(), real_shape_, shape_.begin());
            }
            num = shape_[0];
            channel = shape_[1];
            height = shape_[2];
            width = shape_[3];
        }

        /// Constructor
        /// @brief
        ///
        Shape(const Shape<4> &shape)
        {
            Make(shape);
        }

        /// Returns the size of the shape_
        /// @brief
        /// @return size
        ///
        uint32 dims(size_t index) const noexcept
        {
            if (index >= shape_.size())
            {
                LOG_ERROR("index(%i) out of range.", index);
                return -1;
            }
            return shape_[index];
        }

        /// Returns the size of the shape_
        /// @brief
        /// @return size
        ///
        uint32 size() const noexcept
        {
            return shape_[0] + shape_[1] + shape_[2] + shape_[3];
        }

        /// Returns the shape_ as a string representation
        /// @return std::string
        ///
        virtual std::string str() const
        {
            std::string out = "[";
            for (size_t i = 0; i < shape_.size(); ++i)
            {
                out += std::to_string(shape_[i]);
                if (i != (shape_.size() - 1))
                {
                    out += ",";
                }
            }
            out += "]";
            return out;
        }

        /// operator =
        /// @brief
        /// @param input
        /// @return Shape
        ///
        Shape<4> &operator=(const Shape<4> &shape)
        {
            Make(shape);
            return *this;
        }

        /// Equality operator
        /// @brief
        /// @param InOtherShape
        /// @return bool
        ///
        bool operator==(const Shape &InOtherShape) const noexcept
        {
            return num == InOtherShape.num && channel == InOtherShape.channel && width == InOtherShape.width && height == InOtherShape.height;
        }

    private:
        std::array<uint32, 4> shape_{0};

        void Make(const Shape<4> &shape)
        {
            shape_[0] = shape.shape_[0];
            shape_[1] = shape.shape_[1];
            shape_[2] = shape.shape_[2];
            shape_[3] = shape.shape_[3];
            num = shape_[0];
            channel = shape_[1];
            height = shape_[2];
            width = shape_[3];
        }
    };

    /// IO operator for the Shape class
    /// @param InOStream
    /// @param InShape
    /// @return std::ostream
    ///
    template <uint32 N>
    std::ostream &operator<<(std::ostream &InOStream, const Shape<N> &InShape)
    {
        InOStream << InShape.str();
        return InOStream;
    }
} // namespace ppm
