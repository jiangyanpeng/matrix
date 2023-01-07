cmake_minimum_required(VERSION 3.4)

project(pymatrix)

set(PACKAGE_VERSION ${matrix_VERSION_STRING})
add_definitions(-DVERSION_INFO="${PACKAGE_VERSION}")

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

add_subdirectory(pybind11)

include_directories(${pybind11_INCLUDE_DIR} ${PYTHON_INCLUDE_DIRS})
pybind11_add_module(pymatrix src/main.cpp)
set_target_properties(pymatrix PROPERTIES OUTPUT_NAME "pymatrix")

## add matrix shared lib
add_library(matrix SHARED IMPORTED)
set_target_properties(matrix PROPERTIES IMPORTED_LOCATION /${CMAKE_CURRENT_BINARY_DIR}/../../lib/libmatrix.so)

target_link_libraries(pymatrix PUBLIC matrix)
set_target_properties(pymatrix PROPERTIES PREFIX "" LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
set_property(TARGET pymatrix PROPERTY FOLDER "python")
