#pragma once
#include "Log.h"
#include "Type.hpp"

namespace ppm
{
    //================================================================================
    // Class Description:
    /// Custom const_iterator for NdArray
    template <typename dtype, typename PointerType, typename DifferenceType>
    class MetaConstIterator
    {
    private:
        using self_type = MetaConstIterator<dtype, PointerType, DifferenceType>;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = dtype;
        using pointer = PointerType;
        using reference = const value_type &;
        using difference_type = DifferenceType;

        //============================================================================
        // Method Description:
        /// Default Constructor
        ///
        MetaConstIterator() = default;

        //============================================================================
        // Method Description:
        /// Constructor
        ///
        /// @param ptr: the iterator pointer
        ///
        explicit MetaConstIterator(pointer ptr) : ptr_(ptr)
        {
            if (ptr == nullptr)
            {
                LOG_ERROR("NdArray has not been initialized.");
            }
        }

        //============================================================================
        // Method Description:
        /// Iterator dereference
        ///
        /// @return reference
        ///
        reference operator*() const noexcept
        {
            return *ptr_;
        }

        //============================================================================
        // Method Description:
        /// Iterator pointer operator
        ///
        /// @return pointer
        ///
        pointer operator->() const noexcept
        {
            return ptr_;
        }

        //============================================================================
        // Method Description:
        /// Iterator prefix incrament operator
        ///
        /// @return MetaConstIterator&
        ///
        self_type &operator++() noexcept
        {
            ++ptr_;
            return *this;
        }

        //============================================================================
        // Method Description:
        /// Iterator postfix incrament operator
        ///
        /// @return MetaConstIterator
        ///
        self_type operator++(int) noexcept
        {
            self_type tmp = *this;
            ++*this;
            return tmp;
        }

        //============================================================================
        // Method Description:
        /// Iterator prefix decrament operator
        ///
        /// @return MetaConstIterator&
        ///
        self_type &operator--() noexcept
        {
            --ptr_;
            return *this;
        }

        //============================================================================
        // Method Description:
        /// Iterator postfix decrament operator
        ///
        /// @return MetaConstIterator
        ///
        self_type operator--(int) noexcept
        {
            self_type tmp = *this;
            --*this;
            return tmp;
        }

        //============================================================================
        // Method Description:
        /// Iterator addition assignement operator
        ///
        /// @param offset
        /// @return MetaConstIterator&
        ///
        self_type &operator+=(const difference_type offset) noexcept
        {
            ptr_ += offset;
            return *this;
        }

        //============================================================================
        // Method Description:
        /// Iterator addition operator
        ///
        /// @param offset
        /// @return MetaConstIterator
        ///
        self_type operator+(const difference_type offset) const noexcept
        {
            self_type tmp = *this;
            return tmp += offset;
        }

        //============================================================================
        // Method Description:
        /// Iterator subtraction assignement operator
        ///
        /// @param offset
        /// @return MetaConstIterator&
        ///
        self_type &operator-=(const difference_type offset) noexcept
        {
            return *this += -offset;
        }

        //============================================================================
        // Method Description:
        /// Iterator subtraction operator
        ///
        /// @param offset
        /// @return MetaConstIterator
        ///
        self_type operator-(const difference_type offset) const noexcept
        {
            self_type tmp = *this;
            return tmp -= offset;
        }

        //============================================================================
        // Method Description:
        /// Iterator difference operator
        ///
        /// @param rhs
        /// @return difference_type
        ///
        difference_type operator-(const self_type &rhs) const noexcept
        {
            return ptr_ - rhs.ptr_;
        }

        //============================================================================
        // Method Description:
        /// Iterator access operator
        ///
        /// @param offset
        /// @return reference
        ///
        reference operator[](const difference_type offset) const noexcept
        {
            return *(*this + offset);
        }

        //============================================================================
        // Method Description:
        /// Iterator equality operator
        ///
        /// @param rhs
        /// @return bool
        ///
        bool operator==(const self_type &rhs) const noexcept
        {
            return ptr_ == rhs.ptr_;
        }

        //============================================================================
        // Method Description:
        /// Iterator not-equality operator
        ///
        /// @param rhs
        /// @return bool
        ///
        bool operator!=(const self_type &rhs) const noexcept
        {
            return !(*this == rhs);
        }

        //============================================================================
        // Method Description:
        /// Iterator less than operator
        ///
        /// @param rhs
        /// @return bool
        ///
        bool operator<(const self_type &rhs) const noexcept
        {
            return ptr_ < rhs.ptr_;
        }

        //============================================================================
        // Method Description:
        /// Iterator greater than operator
        ///
        /// @param rhs
        /// @return bool
        ///
        bool operator>(const self_type &rhs) const noexcept
        {
            return rhs < *this;
        }

        //============================================================================
        // Method Description:
        /// Iterator less than equal operator
        ///
        /// @param rhs
        /// @return bool
        ///
        bool operator<=(const self_type &rhs) const noexcept
        {
            return !(rhs < *this);
        }

        //============================================================================
        // Method Description:
        /// Iterator greater than equal operator
        ///
        /// @param rhs
        /// @return bool
        ///
        bool operator>=(const self_type &rhs) const noexcept
        {
            return !(*this < rhs);
        }

        /// string
        std::string str() const
        {
            std::stringstream ss;
            ss << static_cast<void *>(ptr_);
            return ss.str();
        }

    private:
        pointer ptr_{nullptr};
    };

    //============================================================================
    // Method Description:
    /// Iterator addition operator
    ///
    /// @param offset
    /// @param next
    /// @return bool
    ///
    template <class dtype, typename PointerType, typename DifferenceType>
    MetaConstIterator<dtype, PointerType, DifferenceType>
    operator+(typename MetaConstIterator<dtype, PointerType, DifferenceType>::difference_type offset,
              MetaConstIterator<dtype, PointerType, DifferenceType> next) noexcept
    {
        return next += offset;
    }

    //================================================================================
    // Class Description:
    /// Custom iterator for NdArray
    template <typename dtype, typename PointerType, typename DifferenceType>
    class MetaIterator : public MetaConstIterator<dtype, PointerType, DifferenceType>
    {
    private:
        using MyBase = MetaConstIterator<dtype, PointerType, DifferenceType>;
        using self_type = MetaIterator<dtype, PointerType, DifferenceType>;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = dtype;
        using pointer = PointerType;
        using reference = value_type &;
        using difference_type = DifferenceType;

        using MyBase::MyBase;

        //============================================================================
        // Method Description:
        /// Iterator dereference
        ///
        /// @return reference
        ///
        reference operator*() const noexcept
        {
            return const_cast<reference>(MyBase::operator*());
        }

        //============================================================================
        // Method Description:
        /// Iterator pointer operator
        ///
        /// @return pointer
        ///
        pointer operator->() const noexcept
        {
            return const_cast<pointer>(MyBase::operator->());
        }

        //============================================================================
        // Method Description:
        /// Iterator prefix incrament operator
        ///
        /// @return MetaConstIterator&
        ///
        self_type &operator++() noexcept
        {
            MyBase::operator++();
            return *this;
        }

        //============================================================================
        // Method Description:
        /// Iterator postfix incrament operator
        ///
        /// @return MetaConstIterator
        ///
        self_type operator++(int) noexcept
        {
            self_type tmp = *this;
            MyBase::operator++();
            return tmp;
        }

        //============================================================================
        // Method Description:
        /// Iterator prefix decrament operator
        ///
        /// @return MetaConstIterator&
        ///
        self_type &operator--() noexcept
        {
            MyBase::operator--();
            return *this;
        }

        //============================================================================
        // Method Description:
        /// Iterator postfix decrament operator
        ///
        /// @return MetaConstIterator
        ///
        self_type operator--(int) noexcept
        {
            self_type tmp = *this;
            MyBase::operator--();
            return tmp;
        }

        //============================================================================
        // Method Description:
        /// Iterator addition assignement operator
        ///
        /// @param offset
        /// @return MetaConstIterator&
        ///
        self_type &operator+=(const difference_type offset) noexcept
        {
            MyBase::operator+=(offset);
            return *this;
        }

        //============================================================================
        // Method Description:
        /// Iterator addition operator
        ///
        /// @param offset
        /// @return MetaConstIterator
        ///
        self_type operator+(const difference_type offset) const noexcept
        {
            self_type tmp = *this;
            return tmp += offset;
        }
    };

    //============================================================================
    // Method Description:
    /// Iterator addition operator
    ///
    /// @param offset
    /// @param next
    /// @return MetaIterator
    ///
    template <class dtype, typename PointerType, typename DifferenceType>
    MetaIterator<dtype, PointerType, DifferenceType>
    operator+(typename MetaIterator<dtype, PointerType, DifferenceType>::difference_type offset,
              MetaIterator<dtype, PointerType, DifferenceType> next) noexcept
    {
        return next += offset;
    }

    /// IO operator for the Shape class
    /// @param InOStream
    /// @param InShape
    /// @return std::ostream
    ///
    template <class dtype, typename PointerType, typename DifferenceType>
    std::ostream &operator<<(std::ostream &InOStream, MetaIterator<dtype, PointerType, DifferenceType> In)
    {
        InOStream << In.str();
        return InOStream;
    }

    /// IO operator for the Shape class
    /// @param InOStream
    /// @param InShape
    /// @return std::ostream
    ///
    template <class dtype, typename PointerType, typename DifferenceType>
    std::ostream &operator<<(std::ostream &InOStream, MetaConstIterator<dtype, PointerType, DifferenceType> In)
    {
        InOStream << In.str();
        return InOStream;
    }
}
