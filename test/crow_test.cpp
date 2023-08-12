

#include "crow.h"

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/test")([](){
        return "Hello world";
    });

    app.port(18080).multithreaded().run();
}
