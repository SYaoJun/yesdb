 cmake_minimum_required(VERSION 3.5)
 set(CMAKE_CXX_STANDARD 17)
 set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")
 include(gtest)
#  include(crc32c)
#  include(zstd)
find_library(GTEST_LIBRARIES gtest ${THIRD_PARTY_PATH}/install/googletest/lib)
find_library(GTEST_MAIN_LIBRARIES gtest_main ${THIRD_PARTY_PATH}/install/googletest/lib)
include_directories(${THIRD_PARTY_PATH}/install/googletest/include)
 # bin
 add_executable(gtest_test third_party/gtest_test.cpp)
#  add_executable(crc32c_test third_party/crc32c_test.cpp)
#  add_executable(zstd_test third_party/zstd_test.cpp)
#  add_executable(db_bench db_bench.cpp)
 ## dependencies
 add_dependencies(gtest_test gtest gtest_main)
#  add_dependencies(gtest_test crc32c)
 # libraries
 target_link_libraries(gtest_test  ${GTEST_MAIN_LIBRARIES} ${GTEST_LIBRARIES})
#  target_link_libraries(crc32c_test ${CRC32C_LIBRARIES})
#  target_link_libraries(zstd_test ${ZSTD_LIBRARIES})
 # db_bench
#  target_link_libraries(db_bench ${CRC32C_LIBRARIES} ${ZSTD_LIBRARIES} yesdb)