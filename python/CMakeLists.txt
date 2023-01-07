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
target_link_libraries(pymatrix PUBLIC ${CMAKE_CURRENT_BINARY_DIR}../../lib/matrix)
set_target_properties(pymatrix PROPERTIES PREFIX "" LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
set_property(TARGET pymatrix PROPERTY FOLDER "python")
# if("${CMAKE_LIBRARY_OUTPUT_DIRECTORY}" STREQUAL "")
#     add_custom_command(TARGET pymatrix POST_BUILD 
#         COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/matrix/matrix${PYTHON_MODULE_PREFIX}${PYTHON_MODULE_EXTENSION} 
#         ${PROJECT_SOURCE_DIR}/matrix/matrix${PYTHON_MODULE_PREFIX}${PYTHON_MODULE_EXTENSION})
# endif("${CMAKE_LIBRARY_OUTPUT_DIRECTORY}" STREQUAL "")

# configure_file(setup.py.i ${PROJECT_SOURCE_DIR}/setup.py)
