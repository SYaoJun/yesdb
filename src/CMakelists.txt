add_subdirectory(storage)
# collect all object files and generate static lib
add_library(yesdb STATIC ${ALL_OBJECT_FILES})


set(YESDB_LIBS
        yesdb_storage
        )


find_package(Threads REQUIRED)
# crc32c
find_library(CRC_LIBS NAMES crc32c PATHS /urs/local/lib REQUIRED)
# zstd
find_library(ZSTD_LIBS zstd /opt/homebrew/Cellar/zstd/1.5.5/lib REQUIRED)

target_link_libraries(
        yesdb
        ${YESDB_LIBS}
        Threads::Threads
        ${CRC_LIBS}
        ${ZSTD_LIBS}
)


add_executable(yesdb_server main.cpp)
target_link_libraries(yesdb_server PRIVATE yesdb)