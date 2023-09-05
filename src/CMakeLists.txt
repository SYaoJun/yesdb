add_library(yesdb_ STATIC storage/common.cpp storage/server.cpp)
find_package(Threads REQUIRED)
target_link_libraries(yesdb_ PRIVATE crc32c libcuckoo Threads::Threads)

include_directories(include)
add_executable(db_server main.cpp)
target_link_libraries(db_server PRIVATE yesdb_)
