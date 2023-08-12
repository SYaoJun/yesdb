
#include "catch2/catch_test_macros.hpp"
#include <iostream>
#include "server.h"
#include "zstd.h"
#include "art.hpp"



TEST_CASE("art",""){
    art::art<std::string> m;
    std::string value_="world";
  // set k
  m.set("k", &value_);

  // get k
  std::string *ptr = m.get("k");

  std::cout<<*ptr<<std::endl;
  // delete k
  m.del("k");

}