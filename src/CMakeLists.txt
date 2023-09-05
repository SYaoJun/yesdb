add_library(yesdb STATIC storage/common.cpp storage/server.cpp)
find_package(Threads REQUIRED)

set(LIBS ${ZSTD_LIBRARIES} ${CRC32C_LIBRARIES} Threads::Threads)
set(DEPS zstd crc32c)
set(INCLUDES ${CRC32C_INCLUDE_DIR} ${GTEST_INCLUDE_DIR} ${ZSTD_INCLUDE_DIR}
             include/)
target_link_libraries(yesdb PUBLIC ${LIBS})
add_dependencies(yesdb ${DEPS})
target_include_directories(yesdb PUBLIC ${INCLUDES})

add_executable(db_server main.cpp)
target_link_libraries(db_server PRIVATE yesdb)
