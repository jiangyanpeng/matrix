add_library(develop SHARED
	matrix/matrix.cpp
)

target_link_libraries(develop
    ${THIRD_PARTY_LIBS}
)