#pragma once
#include "Type.hpp"
#include "Iterators.h"
#include "Shape.hpp"
#include "Log.h"

#include <string>
#include <type_traits>
#include <utility>
#include <memory>

namespace ppm
{
    namespace meta
    {
        template <typename T, uint32 Dims, class Allocator = std::allocator<T>>
        class Meta
        {
            //====================================Attributes==============================
        private:
            using AllocType = typename std::allocator_traits<Allocator>::template rebind_alloc<T>;
            using AllocTraits = std::allocator_traits<AllocType>;

        public:
            using value_type = T;
            using allocator_type = Allocator;
            using pointer = typename AllocTraits::pointer;
            using const_pointer = typename AllocTraits::const_pointer;
            using reference = T &;
            using const_reference = const T &;
            using size_type = uint32;
            using difference_type = typename AllocTraits::difference_type;

            using iterator = MetaIterator<T, pointer, difference_type>;
            using const_iterator = MetaConstIterator<T, const_pointer, difference_type>;
            using reverse_iterator = std::reverse_iterator<iterator>;
            using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        public:
            //============================================================================
            // Method Description:
            /// Defualt Constructor
            ///
            Meta() = default;
            virtual ~Meta() = default;

            //============================================================================
            // Method Description:
            /// Constructor
            ///
            /// @param inFirst
            /// @param inLast
            ///
            template <typename Iterator,
                      enable_if_t<std::is_same<typename std::iterator_traits<Iterator>::value_type, T>::value, int>>
            Meta(Iterator inFirst, Iterator inLast) : shape_(1, static_cast<uint32>(std::distance(inFirst, inLast))),
                                                      size_(shape_.size())
            {
                LOG_INFO("Meta: size: %i", size_);
                if (size_ > 0)
                {
                    std::copy(inFirst, inLast, begin());
                }
                Make();
            }

            //============================================================================
            // Method Description:
            /// Constructor
            ///
            /// @param inShape
            ///
            explicit Meta(const Shape<Dims> &inShape) : shape_(inShape),
                                                        size_(shape_.size())
            {
                LOG_INFO("Meta: size: %i", size_);
                Make(inShape);
            }

            //============================================================================
            // Method Description:
            /// Constructor
            ///
            /// @param inShape
            ///
            explicit Meta(const Shape<Dims> &inShape, const pointer data) : shape_(inShape),
                                                                            size_(shape_.size()),
                                                                            array_(data)
            {
                Make(inShape);
            }

            //============================================================================
            // Method Description:
            /// iterator to the beginning of the flattened array
            /// @return name
            ///
            uint32 Dim(size_t index) const
            {
                return shape_.dims(index);
            }

            //============================================================================
            // Method Description:
            /// iterator to the beginning of the flattened array
            /// @return name
            ///
            void Reshape(const Shape<Dims> &shape)
            {

                if (shape.size() != shape_.size())
                {
                    LOG_ERROR("Can't Reshape, %s to %s", shape_.str().c_str(), shape.str().c_str());
                    return;
                }
                shape_ = shape;
            }

            //============================================================================
            // Method Description:
            /// iterator to the beginning of the flattened array
            /// @return name
            ///
            const std::string name() const { return name_; }

            //============================================================================
            // Method Description:
            /// iterator to the beginning of the flattened array
            /// @return set
            ///
            void set(std::string name) { name_ = name; }

            //============================================================================
            // Method Description:
            /// iterator to the beginning of the flattened array
            /// @return name
            ///
            const std::string type() const { return "Meta"; }

            //============================================================================
            // Method Description:
            /// iterator to the beginning of the flattened array
            /// @return iterator
            ///
            iterator begin() noexcept
            {
                return iterator(array_);
            }

            //============================================================================
            // Method Description:
            /// iterator to the beginning of the input row
            ///
            /// @param dim
            /// @return iterator
            ///
            iterator begin(size_type dim)
            {
                if (dim >= shape_.size())
                {
                    LOG_ERROR("input %i is greater than the number of in the array.", dim);
                }
                size_type step = 0;
                for (int i = 0; i < dim; ++i)
                    step += shape_[i];
                LOG_DEBUG("step = %i", step);
                return begin() += step;
            }

            //============================================================================
            // Method Description:
            /// const iterator to the beginning of the flattened array
            ///
            /// @return const_iterator
            ///
            const_iterator cbegin() const noexcept
            {
                return const_iterator(array_);
            }

            //============================================================================
            // Method Description:
            /// const iterator to the beginning of the input row
            ///
            /// @param dim
            /// @return const_iterator
            ///
            const_iterator cbegin(size_type dim) const
            {
                if (dim >= shape_.size())
                {
                    LOG_ERROR("input %i is greater than the number of in the array.", dim);
                }
                size_type step = 0;
                for (int i = 0; i < dim; ++i)
                    step += shape_[i];
                LOG_DEBUG("step = %i", step);
                return cbegin() += step;
            }

            //============================================================================
            // Method Description:
            /// iterator to 1 past the end of the flattened array
            /// @return iterator
            ///
            iterator end() noexcept
            {
                return begin() += size_;
            }

            //============================================================================
            // Method Description:
            /// const iterator to 1 past the end of the flattened array
            ///
            /// @return const_iterator
            ///
            const_iterator cend() const noexcept
            {
                return cbegin() += size_;
            }

            //============================================================================
            // Method Description:
            /// Returns a reference the last element of the flattened array.
            ///
            /// @return T
            ///
            reference back() noexcept
            {
                return *(end() - 1);
            }

            //============================================================================
            // Method Description:
            /// Returns a copy of the last element of the flattened array.
            ///
            /// @return T
            ///
            const_reference back() const noexcept
            {
                return *(cend() - 1);
            }

            //============================================================================
            // Method Description:
            /// Returns the raw pointer to the underlying data
            /// @return pointer
            ///
            pointer data() noexcept
            {
                return array_;
            }

            //============================================================================
            // Method Description:
            /// Returns the raw pointer to the underlying data
            /// @return const_pointer
            ///
            const_pointer data() const noexcept
            {
                return array_;
            }

            //============================================================================
            // Method Description:
            /// Fill the array with a scaler value.
            ///
            ///
            /// @param inFillValue
            /// @return None
            ///
            Meta<T, Dims> &fill(value_type inFillValue) noexcept
            {
                std::fill(begin(), end(), inFillValue);
                return *this;
            }

            //============================================================================
            // Method Description:
            /// Return if the NdArray is empty. ie the default constructor
            /// was used.
            ///
            /// @return boolean
            ///
            bool isempty() const noexcept
            {
                return size_ == 0;
            }

            //============================================================================
            // Method Description:
            /// Fills the array with ones
            ///
            ///
            Meta<T, Dims> &ones() noexcept
            {
                fill(T{1});
                return *this;
            }

            //============================================================================
            // Method Description:
            /// Fills the array with zeros
            ///
            ///
            Meta<T, Dims> &zeros() noexcept
            {
                fill(T{0});
                return *this;
            }

            //============================================================================
            // Method Description:
            /// Return the shape of the array
            ///
            ///
            /// @return Shape
            ///
            Shape<Dims> shape() const noexcept
            {
                return shape_;
            }

            //============================================================================
            // Method Description:
            /// Return the size of the array
            ///
            ///
            /// @return size
            ///
            size_type size() const noexcept
            {
                return size_;
            }

            //============================================================================
            // Method Description:
            /// Return the size of the array
            ///
            ///
            /// @return size
            ///
            size_type byte() const noexcept
            {
                return size_ * sizeof(T);
            }

        protected:
            //====================================Attributes==============================
            Shape<Dims> shape_{};
            allocator_type allocator_{};
            size_type size_{0};
            std::string name_{};

            // Endian endianess_{Endian::NATIVE};
            pointer array_{nullptr};
            bool owns_ptr_{false};

        protected:
            //============================================================================
            // Method Description:
            /// Deletes the internal array
            ///
            void Delete() noexcept
            {
                if (owns_ptr_ && array_ != nullptr)
                {
                    allocator_.deallocate(array_, size_);
                }

                array_ = nullptr;
                size_ = 0;
                owns_ptr_ = false;
                // endianess_ = Endian::NATIVE;
            }
            //============================================================================
            // Method Description:
            /// Creates a new internal array
            ///
            void Make()
            {
                if (size_ > 0)
                {
                    array_ = allocator_.allocate(size_);
                    owns_ptr_ = true;
                }
            }

            //============================================================================
            // Method Description:
            /// Creates a new internal array
            ///
            /// @param inShape
            ///
            virtual void Make(const Shape<Dims> &inShape)
            {
                Delete();
                shape_ = inShape;
                size_ = inShape.size();
                Make();
            }
        };

    }
}