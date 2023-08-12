#include <plog/Log.h> // Step1: include the headers
#include "plog/Initializers/RollingFileInitializer.h"
#include "crow.h"
#include "server.h"

#define XLOG "xlog.txt"
#define DB_NAME "yaojun.db"

using namespace yesdb;
int main()
{
    plog::init(plog::debug, XLOG);
    PLOG_DEBUG << "Hello log!"; // long macro
    PLOG_DEBUG << "I am ready!";
    crow::SimpleApp app;
    Yesdb yesdb_instance(DB_NAME);
    yesdb_instance.Open();
    yesdb_instance.Put("yaojun", "yysd!");
    CROW_ROUTE(app, "/yaojun")([&yesdb_instance](){
        std::string value = "hello yesdb!";
        yesdb_instance.Get("yaojun", value);
        return value;
    });

    app.port(18080).multithreaded().run();
    yesdb_instance.Close();
    return 0;
}