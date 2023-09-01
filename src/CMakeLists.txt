add_subdirectory(storage)
# collect all object files and generate static lib
add_library(yesdb STATIC ${ALL_OBJECT_FILES})


set(YESDB_LIBS
        yesdb_storage
        )

target_link_libraries(
        yesdb
        ${YESDB_LIBS}
        ${CRC32C_LIBRARIES}
        ${ZSTD_LIBRARIES}
)
