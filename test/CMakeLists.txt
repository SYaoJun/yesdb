 cmake_minimum_required(VERSION 3.16)
 set(CMAKE_CXX_STANDARD 17)
 # common header
 include_directories(/usr/local/include)
 # art
 include_directories(../third_party/art)
 include_directories(../third_party/art/art)
 # picobench
 include_directories(../third_party/picobench)
 # spdlog
 include_directories(../third_party/spdlog/*)
 # google test
 include(FetchContent)
 FetchContent_Declare(
         googletest
         GIT_REPOSITORY https://github.com/google/googletest.git
         GIT_TAG v1.14.0
 )
 FetchContent_MakeAvailable(googletest)

 # source file
 file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

 # test unit
 foreach (test_source ${SRC_FILES})
     get_filename_component(test_filename ${test_source} NAME)
     string(REPLACE ".cpp" "" test_name ${test_filename})
     message(STATUS, " test file = ${test_name}")
     add_executable(${test_name} ${test_source})
     target_link_libraries(${test_name}
             ${ZSTD_LIBS}
             gtest_main
             yesdb)
 endforeach ()