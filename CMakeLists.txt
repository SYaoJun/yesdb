cmake_minimum_required(VERSION 3.5)
project(yesdb
        VERSION 2023.8
        DESCRIPTION "a key-value storage engine."
        LANGUAGES C CXX
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(THIRD_PARTY_PATH ${CMAKE_CURRENT_BINARY_DIR}/third-party)

include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PROJECT_SOURCE_DIR}/third_party)

include(gtest)
#  include(crc32c)
#  include(zstd)
 # headers 
 include_directories(${GTEST_INCLUDE_DIR})
#  include_directories(${CRC32C_INCLUDE_DIR})
#  include_directories(${ZSTD_INCLUDE_DIR})

# add_subdirectory(src)
add_subdirectory(test)