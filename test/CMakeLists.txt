add_executable(benchmark benchmark.cpp)

target_link_libraries(benchmark
        ${MATRIX_LIBS}
        ${THIRD_PARTY_LIBS}
        )

target_link_libraries(benchmark
        ${THIRD_PARTY_LIBS}
        )