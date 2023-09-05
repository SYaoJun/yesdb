cmake_minimum_required(VERSION 3.5)
project(yesdb C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE DEBUG)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include(FetchContent)
# libcuckoo
FetchContent_Declare(
  libcuckoo
  GIT_REPOSITORY https://github.com/efficient/libcuckoo.git
  GIT_TAG v0.3.1)
FetchContent_MakeAvailable(libcuckoo)
# crc32c
FetchContent_Declare(
  crc32c
  GIT_REPOSITORY https://github.com/google/crc32c.git
  GIT_TAG 1.1.2)
FetchContent_MakeAvailable(crc32c)
# # zstd FetchContent_Declare( zstd GIT_REPOSITORY
# https://github.com/facebook/zstd.git GIT_TAG v1.5.5)
# FetchContent_MakeAvailable(zstd)

include_directories(src/include)
# add_subdirectory(src)

find_package(Threads REQUIRED)

add_executable(db_server main.cpp)
target_link_libraries(db_server yesdb_ crc32c libcuckoo Threads::Threads)
# target_include_directories(db_server PRIVATE ${crc32c_SOURCE_DIR}/crc32c)
