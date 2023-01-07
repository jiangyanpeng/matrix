# pymatrix
python wrapper of matrix with [pybind11](https://github.com/pybind/pybind11), only support python3.x now.


Install from pip
==================

matrix is available as wheel packages for macOS, Windows and Linux distributions, you can install with pip:

```
python -m pip install -U pip
python -m pip install -U pymatrix
```

# Build from source

If you want to build matrix with some options not as default, or just like to build everything yourself, it is not difficult to build matrix from source.

## Prerequisites

**On Unix (Linux, OS X)**

* A compiler with C++11 support
* CMake >= 3.4

**On Mac**

* A compiler with C++11 support
* CMake >= 3.4

**On Windows**

* Visual Studio 2015 or higher
* CMake >= 3.4

## Build
```bash
cd /pathto/matrix
sh build_linux_x86.sh
```

## Install
```bash
python -m pip install -U pip
pip install pybind11
```

if you use conda or miniconda, you can also install as following:
```bash
cd /build/python
sh setup.sh 
```

## Tests

**benchmark**

```bash
cd /build/python
python3 tests/benchmark.py
```

## Numpy
**pymatrix.matrix->numpy.array, with no memory copy**

```bash
import pymatrix
mat = pymatrix.matrix(...)
mat_np = np.array(mat)
```

**numpy.array->matrix.Mat, with no memory copy**
```bash
import pymatrix
mat_np = np.array(...)
mat = pymatrix.matrix(mat_np)
```