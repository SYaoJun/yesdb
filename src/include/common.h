#pragma once

#include <cstdint>
#include <ctime>
#include <memory>
#include <string>

namespace yesdb {

uint32_t timestamp();

uint32_t crc32_checksum(const char *, size_t);

template <typename... Args>
static std::string str_format(const std::string &format, Args... args) {
  auto size_buf = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;
  std::unique_ptr<char[]> buf(new (std::nothrow) char[size_buf]);

  if (!buf)
    return std::string("");

  std::snprintf(buf.get(), size_buf, format.c_str(), args...);
  return std::string(buf.get(), buf.get() + size_buf - 1);
}
} // namespace yesdb
