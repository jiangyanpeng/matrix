#include <iostream>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <pybind11/functional.h>

namespace py = pybind11;

PYBIND11_MODULE(matrix, m)
{
    m.def("__version__", []()
          { return "0.0.1"; });
}