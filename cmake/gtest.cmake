INCLUDE(ExternalProject)

SET(GTEST_SOURCES_DIR ${CMAKE_SOURCE_DIR}/contrib/googletest/)
SET(GTEST_BUILD_DIR ${THIRD_PARTY_PATH}/src/extern_googletest/)
SET(GTEST_INSTALL_DIR ${THIRD_PARTY_PATH}/install/googletest)

set(GTEST_CONFIGURE cd ${GTEST_BUILD_DIR} && cmake -B build -DCMAKE_INSTALL_PREFIX=${GTEST_INSTALL_DIR}) 
set(GTEST_MAKE cd ${GTEST_BUILD_DIR} && cmake --build build) 
set(GTEST_INSTALL cd ${GTEST_BUILD_DIR} && cmake --install build)

FILE(WRITE ${GTEST_BUILD_DIR}/src/copy_repo.sh
        "mkdir -p ${GTEST_BUILD_DIR} && cp -rf ${GTEST_SOURCES_DIR}/* ${GTEST_BUILD_DIR}")

execute_process(COMMAND sh ${GTEST_BUILD_DIR}/src/copy_repo.sh)

ExternalProject_Add(
        extern_googletest
        SOURCE_DIR ${GTEST_SOURCES_DIR}
        PREFIX ${GTEST_INSTALL_DIR}
        BUILD_IN_SOURCE 1
        CONFIGURE_COMMAND ${GTEST_CONFIGURE}
        BUILD_COMMAND ${GTEST_MAKE}
        INSTALL_COMMAND ${GTEST_INSTALL}
)

find_library(GTEST_LIBRARIES gtest ${GTEST_INSTALL_DIR}/lib)
find_library(GTEST_MAIN_LIBRARIES gtest_main ${GTEST_INSTALL_DIR}/lib)

set(GTEST_INCLUDE_DIR ${GTEST_INSTALL_DIR}/include)