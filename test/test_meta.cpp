#include "Meta.hpp"
#include "tensor/Tensor.hpp"

int main()
{
    std::cout << "Meta Test" << std::endl;
    ppm::tensor::Tensor<float> tensor(1, 2, 3, 4);
    tensor.set("Tensor");
    auto tmp = tensor.fill(1);
    // auto shape = tensor.shape();
    // std::cout << "tmp: " << tmp.data() << std::endl;
    std::cout << "name: " << tensor.name() << std::endl;
    std::cout << "ptr: " << tensor.data() << std::endl;
    std::cout << "inter: " << tensor.begin() << std::endl;
    std::cout << "inter: " << tensor.end() << std::endl;
    std::cout << "size: " << tensor.size() << std::endl;
    std::cout << "dims: " << tensor.shape() << std::endl;
    std::cout << "byte: " << tensor.byte() << std::endl;
    std::cout << "str: " << tensor.str() << std::endl;
    std::cout << "type: " << tensor.type() << std::endl;
    tensor.Reshape({2, 1, 3, 4});
    std::cout << "dims: " << tensor.shape() << std::endl;
    return 0;
}