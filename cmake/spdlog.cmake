include(ExternalProject)

set(SPDLOG_ROOT ${CMAKE_BINARY_DIR}/thirdparty/SPDLOG)
set(SPDLOG_GIT_TAG  v1.6.0)  
set(SPDLOG_GIT_URL      https://gitee.com/roberchen/spdlog.git)  
set(SPDLOG_CONFIGURE    cd ${SPDLOG_ROOT}/src/SPDLOG && cmake -B build -DCMAKE_INSTALL_PREFIX=${SPDLOG_ROOT})  
set(SPDLOG_MAKE         cd ${SPDLOG_ROOT}/src/SPDLOG/build && cmake --build .)  
set(SPDLOG_INSTALL      cd ${SPDLOG_ROOT}/src/SPDLOG/build && cmake --install .)  

ExternalProject_Add(SPDLOG
        PREFIX            ${SPDLOG_ROOT}
        GIT_REPOSITORY    ${SPDLOG_GIT_URL}
        GIT_TAG           ${SPDLOG_GIT_TAG}
        CONFIGURE_COMMAND ${SPDLOG_CONFIGURE}
        BUILD_COMMAND     ${SPDLOG_MAKE}
        INSTALL_COMMAND   ${SPDLOG_INSTALL}
)

set(SPDLOG_LIBRARIES ${SPDLOG_ROOT}/lib/libspdlog.a)
set(SPDLOG_INCLUDE_DIRS ${SPDLOG_ROOT}/include)