 cmake_minimum_required(VERSION 3.16)

 set(CMAKE_CXX_STANDARD 17)

 include_directories(/Users/yaojun/MyInstall/catch_install/include)
 include_directories(/opt/homebrew/Cellar/zstd/1.5.5/include)
 find_library(CATCH2_LIBS Catch2 /Users/yaojun/MyInstall/catch_install/lib REQUIRED)
 find_library(CATCH2MAIN_LIBS Catch2Main /Users/yaojun/MyInstall/catch_install/lib REQUIRED)
 find_library(ZSTD_LIBS zstd /opt/homebrew/Cellar/zstd/1.5.5/lib REQUIRED)
 file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")
# art
 include_directories(../third_party/art)
  include_directories(../third_party/art/art)
 #picobench
 include_directories(../third_party/picobench)

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