include(ExternalProject)

set(GTEST_ROOT ${CMAKE_BINARY_DIR}/thirdparty/googletest)
set(GTEST_GIT_TAG  v1.13.0)  
set(GTEST_GIT_URL      https://gitee.com/mirrors/googletest.git)  
set(GTEST_CONFIGURE    cd ${GTEST_ROOT}/src/GTEST && cmake -DCMAKE_INSTALL_PREFIX=${GTEST_ROOT} .)  
set(GTEST_MAKE         cd ${GTEST_ROOT}/src/GTEST && make -j 8)  
set(GTEST_INSTALL      cd ${GTEST_ROOT}/src/GTEST && make install)  

ExternalProject_Add(GTEST
        PREFIX            ${GTEST_ROOT}
        GIT_REPOSITORY    ${GTEST_GIT_URL}
        GIT_TAG           ${GTEST_GIT_TAG}
        CONFIGURE_COMMAND ${GTEST_CONFIGURE}
        BUILD_COMMAND     ${GTEST_MAKE}
        INSTALL_COMMAND   ${GTEST_INSTALL}
)

set(GTEST_LIBRARIES ${GTEST_ROOT}/lib/libgtest.a ${GTEST_ROOT}/lib/libgtest_main.a)
set(GTEST_INCLUDE_DIRS ${GTEST_ROOT}/include)