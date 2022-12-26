cmake_minimum_required(VERSION 3.10)
project(matrix)

SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS "-std=c++11 -march=native -O3")
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin )
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib )
if(CMAKE_COMPILER_IS_GNUCXX)
    # IEEE754
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11 -frounding-math -fsignaling-nans")
else()
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif(CMAKE_COMPILER_IS_GNUCXX)

####### DEPENDENCIES #######
# FIND_PACKAGE(OpenCV 3 REQUIRED)
# IF(OpenCV_FOUND)
#     message(STATUS "OPENCV is enabled")
#     message(STATUS "OpenCV_INCLUDE_DIRS=${OpenCV_INCLUDE_DIRS}")
#     message(STATUS "OpenCV_LIBS=${OpenCV_LIBS}")
# ELSE()
#     message(STATUS "OPENCV is disabled or not found, " ${TARGET_NAME} " skiped")
#     return()
# ENDIF()
#FIND_PACKAGE(InferenceEngine 2.0 REQUIRED)

####### INCLUDE #######
INCLUDE_DIRECTORIES(
        ${PROJECT_SOURCE_DIR}/include
)

####### SOURCES (Projects) #######
# INCLUDE_DIRECTORIES(
#         # ${PROJECT_SOURCE_DIR}/develop
#         ${PROJECT_SOURCE_DIR}/develop/*cpp
# )
ADD_SUBDIRECTORY(develop)

####### LIBS #######
# thirdparty
SET(THIRD_PARTY_LIBS
    # ${OpenCV_LIBS}
    #${EIGEN3_LIBS}
)

# INTERNAL LIBS #
SET(MATRIX_LIBS
    matrix
)

####### BUILDING MIAN #######
ADD_SUBDIRECTORY(test)