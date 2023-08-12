#include "catch2/catch_test_macros.hpp"
#include <iostream>
#include "server.h"
#include "zstd.h"
using namespace yesdb;

TEST_CASE("test_yesdb_write_and_read", "yesdb.db"){
     Yesdb yesdb("yesdb.db");
     yesdb.Open();
     std::string key = "yaojun";
     std::string value = "A database developer";
     bool ret = yesdb.Put(key, value);
     REQUIRE(ret == true);
     yesdb.Sync();
     std::string ret_value;
     ret = yesdb.Get(key, ret_value);
     REQUIRE(ret == true);
     REQUIRE(value == ret_value);
     yesdb.Close();
}

