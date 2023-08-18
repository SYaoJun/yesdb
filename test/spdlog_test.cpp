#include "spdlog/spdlog.h"

// 在随便一个地方
// Use the default logger (stdout, multi-threaded, colored)
int main() { spdlog::info("Hello, {}!", "World"); }
