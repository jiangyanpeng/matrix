add_library(matrix SHARED
    Log.cpp
	matrix/Matrix.cpp
    tensor/Tensor.cpp
)

target_link_libraries(matrix
    ${THIRD_PARTY_LIBS}
)