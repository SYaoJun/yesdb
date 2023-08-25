#include "server.h"
#include <iostream>
#define PICOBENCH_IMPLEMENT_WITH_MAIN
#include "picobench.hpp"

#include <cstdlib>
#include <string>

using namespace yesdb;

static void put_test(picobench::state &s) {
  Yesdb yesdb("yesdb.db");
  yesdb.Open();
  for (auto _ : s) {
    std::string key = "yaojun" + std::to_string(rand());
    std::string value = "A database developer";
    bool ret = yesdb.Put(key, value);
  }
}

PICOBENCH(put_test).samples(2).iterations({100, 1000, 10000});
