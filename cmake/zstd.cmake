INCLUDE(ExternalProject)

SET(ZSTD_SOURCES_DIR ${THIRD_PARTY_PATH}/src/extern_zstd/)
SET(ZSTD_INSTALL_DIR ${THIRD_PARTY_PATH}/install/zstd)

set(ZSTD_MAKE cd ${ZSTD_SOURCES_DIR} && make) 
set(ZSTD_INSTALL cd ${ZSTD_SOURCES_DIR} && make install prefix=${ZSTD_INSTALL_DIR})

FILE(WRITE ${ZSTD_SOURCES_DIR}/src/copy_repo.sh
        "mkdir -p ${ZSTD_SOURCES_DIR} && cp -rf ${CMAKE_SOURCE_DIR}/contrib/zstd/* ${ZSTD_SOURCES_DIR}")

execute_process(COMMAND sh ${ZSTD_SOURCES_DIR}/src/copy_repo.sh)

ExternalProject_Add(
        extern_zstd
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/contrib/zstd/
        PREFIX ${ZSTD_INSTALL_DIR}
        BUILD_IN_SOURCE 1
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ${ZSTD_MAKE}
        INSTALL_COMMAND ${ZSTD_INSTALL}
)

find_library(ZSTD_LIBRARIES zstd ${ZSTD_INSTALL_DIR}/lib)
set(ZSTD_INCLUDE_DIR ${ZSTD_INSTALL_DIR}/include)