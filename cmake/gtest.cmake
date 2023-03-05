# 添加第三方依赖包
include(FetchContent)
# FetchContent_MakeAvailable was not added until CMake 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(add_FetchContent_MakeAvailable.cmake)
endif()

set(GTEST_GIT_TAG  v1.12.0)  # 指定版本
set(GTEST_GIT_URL  https://github.com/google/googletest)  # 指定git仓库地址

FetchContent_Declare(
  googletest
  GIT_REPOSITORY    ${GTEST_GIT_URL}
  GIT_TAG           ${GTEST_GIT_TAG}
)

FetchContent_MakeAvailable(googletest)