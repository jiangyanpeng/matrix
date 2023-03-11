#pragma once

#include "Meta.hpp"

namespace ppm
{
    namespace tensor
    {
        template <typename T>
        class Tensor : public meta::Meta<T, 4>
        {
        public:
            Tensor() = default;
            ~Tensor() = default;

            Tensor(uint32 n, uint32 c, uint32 w, uint32 h)
            {
                meta::Meta<T, 4>::Make(Shape<4>({n, c, w, h}));
            }

            Tensor(uint32 b, uint32 n, uint32 w, uint32 h, const T *data)
            {
                meta::Meta<T, 4>::Make(Shape<4>({b, n, w, h}));
                meta::Meta<T, 4>::array_ = data;
            }

            //============================================================================
            // Method Description:
            /// iterator to the beginning of the flattened array
            /// @return name
            ///
            const std::string type() const { return "Tensor"; }

            const std::string str() const
            {
                int dump_size = std::min(50, int(meta::Meta<T, 4>::size()));
                std::stringstream ss;
                ss << "Tensor<" << meta::Meta<T, 4>::shape_.num << "," << meta::Meta<T, 4>::shape_.channel << ","
                   << meta::Meta<T, 4>::shape_.height << "," << meta::Meta<T, 4>::shape_.width << ">:\n";
                for (size_t i = 0; i < dump_size; i++)
                {
                    ss << meta::Meta<T, 4>::array_[i];
                    if (i != dump_size - 1)
                    {
                        ss << ", ";
                    }
                }
                return ss.str();
            }
        };
    }
}