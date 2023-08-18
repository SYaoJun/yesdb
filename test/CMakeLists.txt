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

 find_library(CATCH2_LIBS Catch2 /usr/local/include REQUIRED)
 find_library(CATCH2MAIN_LIBS Catch2Main /usr/local/lib REQUIRED)
 find_library(ZSTD_LIBS zstd /usr/local/lib REQUIRED)

 file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")


 foreach (test_source ${SRC_FILES})
     get_filename_component(test_filename ${test_source} NAME)
     string(REPLACE ".cpp" "" test_name ${test_filename})
     message(STATUS, " test file = ${test_name}")
     add_executable(${test_name} ${test_source})
     target_link_libraries(${test_name}
             ${CATCH2_LIBS}
             ${CATCH2MAIN_LIBS}
             ${ZSTD_LIBS}
             yesdb)
 endforeach ()