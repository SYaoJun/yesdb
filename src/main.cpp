#include "crow.h"
#include "plog/Initializers/RollingFileInitializer.h"
#include "server.h"
#include <plog/Log.h>

#define XLOG "xlog.txt"
#define DB_NAME "yaojun.db"

using namespace yesdb;

int main() {
  plog::init(plog::debug, XLOG);
  crow::SimpleApp app;
  Yesdb yesdb_instance(DB_NAME);
  yesdb_instance.Open();
  yesdb_instance.Put("yesdb", "welcome to the magic world!\n");
  CROW_ROUTE(app, "/yesdb")
  ([&yesdb_instance]() {
    std::string value = "hello yesdb!\n";
    yesdb_instance.Get("yesdb", value);
    return value;
  });

  app.port(18080).multithreaded().run();
  yesdb_instance.Close();
  return 0;
}