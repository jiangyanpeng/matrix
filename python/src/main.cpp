#include <iostream>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <pybind11/functional.h>

namespace py = pybind11;

PYBIND11_MODULE(pymatrix, m)
{
    m.attr("__version__") = "0.0.1";
}