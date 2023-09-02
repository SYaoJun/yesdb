cmake_minimum_required(VERSION 3.5)
project(yesdb C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(THIRD_PARTY_PATH ${CMAKE_CURRENT_BINARY_DIR}/third-party)

include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PROJECT_SOURCE_DIR}/third_party)
enable_testing()
include(gtest)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
#  include(crc32c)
#  include(zstd)
set(DYNAMIC_LIB
    ${GTEST_MAIN_LIBRARIES}
    ${GTEST_LIBRARIES}
    Threads::Threads
    )

set(DEPEND_LIBS
    gtest
    )

# add_subdirectory(src)
# add_subdirectory(test)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(gtest_test test/third_party/gtest_test.cpp)
add_dependencies(gtest_test ${DEPEND_LIBS})

target_link_libraries(gtest_test ${DYNAMIC_LIB})

add_test(NAME mytest COMMAND $<TARGET_FILE:gtest_test>)