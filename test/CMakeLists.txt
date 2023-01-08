file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
foreach(FILE ${files})
#     message("-- ${FILE}")
      get_filename_component(EXECUTABLE_NAME ${FILE} NAME_WE)
      add_executable(${EXECUTABLE_NAME} ${FILE})
      target_link_libraries(${EXECUTABLE_NAME} PUBLIC
        ${MATRIX_LIBS}
        ${THIRD_PARTY_LIBS}
      )
endforeach(FILE ${SOURCE_FILES})