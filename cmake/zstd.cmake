include(ExternalProject)

set(ZSTD_ROOT ${CMAKE_BINARY_DIR}/thirdparty/zstd)
set(ZSTD_GIT_TAG v1.4.0)
set(ZSTD_GIT_URL https://gitee.com/avgo/zstd.git)
set(ZSTD_MAKE cd ${ZSTD_ROOT}/src/extern_zstd && make)
set(ZSTD_INSTALL cd ${ZSTD_ROOT}/src/extern_zstd && make install
                 prefix=${ZSTD_ROOT})

ExternalProject_Add(
  extern_zstd
  PREFIX ${ZSTD_ROOT}
  GIT_REPOSITORY ${ZSTD_GIT_URL}
  GIT_TAG ${ZSTD_GIT_TAG}
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ${ZSTD_MAKE}
  INSTALL_COMMAND ${ZSTD_INSTALL}
  BUILD_BYPRODUCTS "")

find_library(ZSTD_LIBRARIES zstd ${ZSTD_ROOT}/lib/)
set(ZSTD_INCLUDE_DIR ${ZSTD_ROOT}/include)

add_library(zstd STATIC IMPORTED GLOBAL)
set_property(TARGET zstd PROPERTY IMPORTED_LOCATION ${ZSTD_LIBRARIES})
add_dependencies(zstd extern_zstd)
