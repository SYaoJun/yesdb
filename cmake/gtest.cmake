include(ExternalProject)

set(GTEST_ROOT ${CMAKE_BINARY_DIR}/thirdparty/googletest)
set(GTEST_GIT_TAG v1.13.0)
set(GTEST_GIT_URL https://gitee.com/mirrors/googletest.git)
set(GTEST_CONFIGURE cd ${GTEST_ROOT}/src/extern_gtest && cmake
                    -DCMAKE_INSTALL_PREFIX=${GTEST_ROOT} .)
set(GTEST_MAKE cd ${GTEST_ROOT}/src/extern_gtest && make -j 8)
set(GTEST_INSTALL cd ${GTEST_ROOT}/src/extern_gtest && make install)

ExternalProject_Add(
  extern_gtest
  PREFIX ${GTEST_ROOT}
  GIT_REPOSITORY ${GTEST_GIT_URL}
  GIT_TAG ${GTEST_GIT_TAG}
  CONFIGURE_COMMAND ${GTEST_CONFIGURE}
  BUILD_COMMAND ${GTEST_MAKE}
  INSTALL_COMMAND ${GTEST_INSTALL}
  BUILD_BYPRODUCTS ${GTEST_ROOT}/lib/libgtest.a)

set(GTEST_LIBRARIES ${GTEST_ROOT}/lib/libgtest.a)
set(GTEST_MAIN_LIBRARIES ${GTEST_ROOT}/lib/libgtest_main.a)
set(GMOCK_LIBRARIES ${GTEST_ROOT}/lib/libgmock.a)
set(GMOCK_MAIN_LIBRARIES ${GTEST_ROOT}/lib/libgmock_main.a)
set(GTEST_INCLUDE_DIR ${GTEST_ROOT}/include)

add_library(gtest STATIC IMPORTED GLOBAL)
add_library(gtest_main STATIC IMPORTED GLOBAL)
add_library(gmock STATIC IMPORTED GLOBAL)
add_library(gmock_main STATIC IMPORTED GLOBAL)
set_property(TARGET gtest PROPERTY IMPORTED_LOCATION ${GTEST_LIBRARIES})
set_property(TARGET gtest_main PROPERTY IMPORTED_LOCATION
                                        ${GTEST_MAIN_LIBRARIES})
set_property(TARGET gmock PROPERTY IMPORTED_LOCATION ${GMOCK_LIBRARIES})
set_property(TARGET gmock_main PROPERTY IMPORTED_LOCATION
                                        ${GMOCK_MAIN_LIBRARIES})
add_dependencies(gtest extern_gtest)
add_dependencies(gtest_main extern_gtest)
add_dependencies(gmock extern_gtest)
add_dependencies(gmock_main extern_gtest)
