include(ExternalProject)

set(ZSTD_ROOT ${CMAKE_BINARY_DIR}/thirdparty/zstd)
set(ZSTD_GIT_TAG  v1.4.0)  
set(ZSTD_GIT_URL      https://gitee.com/avgo/zstd.git)    
set(ZSTD_MAKE         cd ${ZSTD_ROOT}/src/ZSTD && make)  
set(ZSTD_INSTALL      cd ${ZSTD_ROOT}/src/ZSTD && make install prefix=${ZSTD_ROOT})  

ExternalProject_Add(ZSTD
        PREFIX            ${ZSTD_ROOT}
        GIT_REPOSITORY    ${ZSTD_GIT_URL}
        GIT_TAG           ${ZSTD_GIT_TAG}
        CONFIGURE_COMMAND ""
        BUILD_COMMAND     ${ZSTD_MAKE}
        INSTALL_COMMAND   ${ZSTD_INSTALL}
)

find_library(ZSTD_LIBRARIES zstd ${ZSTD_ROOT}/lib)
set(ZSTD_INCLUDE_DIRS ${ZSTD_ROOT}/include)