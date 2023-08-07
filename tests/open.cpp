// #define CATCH_CONFIG_MAIN
// #include "catch.hpp"
#include <iostream>
#include "server_api.h"
#include "common.h"
#include <string>
using namespace yesdb;

int main(){
    Yesdb yesdb("hello.db");
    const char* key =  "yaojun";
    const char* value = "2023-hello-world";
    bool ret = yesdb.Put(key, value);
    std::cout<<ret<<std::endl;
    // REQUIRE(ret == true);
}