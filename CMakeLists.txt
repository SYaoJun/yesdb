cmake_minimum_required(VERSION 3.16)
project(yesdb
        VERSION 2023.8
        DESCRIPTION "a key-value storage engine."
        LANGUAGES C CXX
        )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE RELESE)

# static library
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)
# shared library
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_LIST_DIR}/bin)
# executable file
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

# install directory
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)

# public header
set(BUSTUB_SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)
set(BUSTUB_THIRD_PARTY_INCLUDE_DIR
        ${PROJECT_SOURCE_DIR}/third_party
        ${PROJECT_SOURCE_DIR}/third_party/catch/
        )

include_directories(${BUSTUB_SRC_INCLUDE_DIR} ${BUSTUB_THIRD_PARTY_INCLUDE_DIR})
include_directories(/usr/local/include)
# zstd include
include_directories(/opt/homebrew/Cellar/zstd/1.5.5/include)

add_subdirectory(src)
add_subdirectory(test)