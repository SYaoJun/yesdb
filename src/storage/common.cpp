#include "common.h"
#include "crc32c/crc32c.h"

namespace yesdb {

uint32_t timestamp() { return static_cast<uint32_t>(time(0)); }

uint32_t crc32_checksum(const char *data, size_t length) {
  return crc32c::Crc32c(data, length);
}

} // namespace yesdb
