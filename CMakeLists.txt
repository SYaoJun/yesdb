cmake_minimum_required(VERSION 3.27)
project(yesdb C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE DEBUG)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include(FetchContent) # libcuckoo
FetchContent_Declare(
  libcuckoo
  GIT_REPOSITORY https://github.com/efficient/libcuckoo.git
  GIT_TAG v0.3.1)
FetchContent_MakeAvailable(libcuckoo) # crc32c
FetchContent_Declare(
  crc32c
  GIT_REPOSITORY https://github.com/google/crc32c.git
  GIT_TAG 1.1.2)
FetchContent_MakeAvailable(crc32c)
# zstd
FetchContent_Declare(
  zstd
  GIT_REPOSITORY https://github.com/facebook/zstd.git
  GIT_TAG v1.5.5)
FetchContent_MakeAvailable(zstd)

add_subdirectory(src)
