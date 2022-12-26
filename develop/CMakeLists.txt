add_library(matrix SHARED
	matrix/Matrix.cpp
)

target_link_libraries(matrix
    ${THIRD_PARTY_LIBS}
)