include(ExternalProject)

set(CRC32C_ROOT ${CMAKE_BINARY_DIR}/thirdparty/crc32c)
set(CRC32C_GIT_TAG 1.1.2)
set(CRC32C_GIT_URL https://gitee.com/kiritoxkiriko/crc32c.git)
set(CRC32C_CONFIGURE cd ${CRC32C_ROOT}/src/extern_crc32c && cmake
                     -DCMAKE_INSTALL_PREFIX=${CRC32C_ROOT} .)
set(CRC32C_MAKE cd ${CRC32C_ROOT}/src/extern_crc32c && make -j 8)
set(CRC32C_INSTALL cd ${CRC32C_ROOT}/src/extern_crc32c && make install)

ExternalProject_Add(
  extern_crc32c
  PREFIX ${CRC32C_ROOT}
  GIT_REPOSITORY ${CRC32C_GIT_URL}
  GIT_TAG ${CRC32C_GIT_TAG}
  CONFIGURE_COMMAND ${CRC32C_CONFIGURE}
  BUILD_COMMAND ${CRC32C_MAKE}
  INSTALL_COMMAND ${CRC32C_INSTALL}
  BUILD_BYPRODUCTS "")

find_library(CRC32C_LIBRARIES crc32c ${CRC32C_ROOT}/lib)
set(CRC32C_INCLUDE_DIR ${CRC32C_ROOT}/include)

add_library(crc32c STATIC IMPORTED GLOBAL)
set_property(TARGET crc32c PROPERTY IMPORTED_LOCATION ${CRC32C_LIBRARIES})
add_dependencies(crc32c extern_crc32c)
