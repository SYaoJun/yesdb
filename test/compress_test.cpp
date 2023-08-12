#include "catch2/catch_test_macros.hpp"
#include <iostream>
#include "server.h"
#include "zstd.h"
#include <vector>
using namespace yesdb;
TEST_CASE("test_yesdb_compress", "test2"){
     Yesdb yesdb("xx.db");
     yesdb.Open();
    std::string originalData = "Hello, this is fdasdfaaaaaaaaaasdfasdfasdf"
                               "jasdhjfoahsdfoahsodfhaoshdifahodfhoashdfoiahsio"
                               "some data to be compressed using Zstandard.";
     std::vector<char> compressed_data;
     std::string decompressed_data;
     int sz = 0;
     yesdb.Compress(originalData, compressed_data, sz);
     yesdb.Decompress(compressed_data, decompressed_data, sz, originalData.size());
     REQUIRE(decompressed_data == originalData);
     yesdb.Close();
}


