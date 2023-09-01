INCLUDE(ExternalProject)

SET(CRC32C_SOURCES_DIR ${CMAKE_SOURCE_DIR}/contrib/crc32c/)
SET(CRC32C_BUILD_DIR ${THIRD_PARTY_PATH}/src/extern_crc32c/)
SET(CRC32C_INSTALL_DIR ${THIRD_PARTY_PATH}/install/crc32c)

set(CRC32C_CONFIGURE cd ${CRC32C_BUILD_DIR} && cmake -B build -DCMAKE_INSTALL_PREFIX=${CRC32C_INSTALL_DIR}) 
set(CRC32C_MAKE cd ${CRC32C_BUILD_DIR} && cmake --build build) 
set(CRC32C_INSTALL cd ${CRC32C_BUILD_DIR} && cmake --install build)

FILE(WRITE ${CRC32C_BUILD_DIR}/src/copy_repo.sh
        "mkdir -p ${CRC32C_BUILD_DIR} && cp -rf ${CRC32C_SOURCES_DIR}/* ${CRC32C_BUILD_DIR}")

execute_process(COMMAND sh ${CRC32C_BUILD_DIR}/src/copy_repo.sh)

ExternalProject_Add(
        extern_crc32c
        SOURCE_DIR ${CRC32C_SOURCES_DIR}
        PREFIX ${CRC32C_INSTALL_DIR}
        BUILD_IN_SOURCE 1
        CONFIGURE_COMMAND ${CRC32C_CONFIGURE}
        BUILD_COMMAND ${CRC32C_MAKE}
        INSTALL_COMMAND ${CRC32C_INSTALL}
)

find_library(CRC32C_LIBRARIES crc32c ${CRC32C_INSTALL_DIR}/lib)
ADD_LIBRARY(crc32c STATIC IMPORTED GLOBAL)
SET_PROPERTY(TARGET crc32c PROPERTY IMPORTED_LOCATION ${CRC32C_LIBRARIES})
set(CRC32C_INCLUDE_DIR ${CRC32C_INSTALL_DIR}/include)
ADD_DEPENDENCIES(crc32c extern_crc32c)