add_library(
        yesdb_storage
        OBJECT
        server.cpp
        common.cpp
)


set(ALL_OBJECT_FILES
        ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:yesdb_storage>
        PARENT_SCOPE)