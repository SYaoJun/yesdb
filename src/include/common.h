#pragma once

#include <string>
#include <ctime>
namespace yesdb {

uint32_t timestamp();

uint32_t crc32_checksum(const char* , size_t);

}


