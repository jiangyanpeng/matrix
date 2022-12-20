add_library(matrix SHARED
	matrix/matrix.cpp
)

target_link_libraries(matrix
    ${THIRD_PARTY_LIBS}
)