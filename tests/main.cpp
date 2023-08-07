#include <iostream>
#include <ctime>
int add_(int a, int b) {
    return a+b;
}
uint32_t timestamp() { return static_cast<uint32_t>(time(0)); }
int main() {
    std::cout<<timestamp()<<std::endl;
    return 0;
}