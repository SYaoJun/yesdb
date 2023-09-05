#include <iostream>
#include <string>
#include <tuple>
#include "server.h"
using namespace yesdb;
void do_put() {}
void do_get() {}
std::tuple<int, int, Option> parse_input(std::string s) {}
void run() {
    std::cout << "welcome to yesdb version 1.0.\n";
    while (true) {
        std::cout << ">";
        std::string input_string;
        std::cin >> input_string;
        auto [key, value, option] = parse_input(input_string);
        switch (option) {
            case Option::PUT:
                do_put();
                break;
            case Option::GET:
                do_get();
                break;
            default:
                exit(0);
        }
    }
}
int main() {
    DBImpl instance("yaojun");
    instance.Open();
    // instance.LoadIndex();
    // instance.AutoMerge();
    run();
    return 0;
}