
#include "server.h"
#include "common.h"
#include "zstd.h"
#include <plog/Log.h>
#include <vector>
/*
 * +-------+--------+--------+----------+-----+-------+
 * | crc32 | tstamp | key_sz | value_sz | key | value |
 * +-------+--------+--------+----------+-----+-------+
 */

namespace yesdb {
Yesdb::Yesdb(std::string filename) : filename_(filename) {}

Yesdb::~Yesdb() {}

bool Yesdb::Open() {
  fd_ = open(filename_.data(), O_RDWR | O_CREAT);
  if (fd_ == -1) {
    PLOG_DEBUG << "can not open the file\n";
    return false;
  }
  PLOG_DEBUG << "successful to open the file\n";
  offset_ = 0;
  return true;
}

bool Yesdb::Put(const std::string key, const std::string value) {
  if (fd_ == -1) {
    PLOG_DEBUG << "file don't open.\n";
    return false;
  }
  std::unique_lock lock(mutex);
  uint32_t key_sz = key.length();
  uint32_t value_sz = value.length();
  char buffer[BUFSIZ];
  // calculate checksum
  int pos = 0;
  uint32_t tstamp = timestamp();
  uint32_t uint32_sz = sizeof(uint32_t);
  memcpy(buffer + pos, &tstamp, uint32_sz);
  pos += uint32_sz;
  memcpy(buffer + pos, &key_sz, uint32_sz);
  pos += uint32_sz;
  memcpy(buffer + pos, &value_sz, uint32_sz);
  pos += uint32_sz;
  memcpy(buffer + pos, key.data(), key_sz);
  pos += key_sz;
  memcpy(buffer + pos, value.data(), value_sz);
  pos += value_sz;
  uint32_t checksum = crc32_checksum(buffer, pos);

  char sup_buffer[BUFSIZ];
  uint32_t new_pos = 0;
  memcpy(sup_buffer + new_pos, &checksum, uint32_sz);
  new_pos += uint32_sz;
  memcpy(sup_buffer + new_pos, buffer, pos);
  new_pos += pos;
  lseek(fd_, offset_, SEEK_SET);
  int ret = write(fd_, sup_buffer, new_pos);
  if (ret < 0) {
    PLOG_DEBUG << "write failed.\n";
    return false;
  }

  Entry entry(fd_, offset_, new_pos);
  offset_ += new_pos;
  key_dir[key] = entry;
  return true;
}

Entry::Entry(int fd, int offset, int size)
    : fd_(fd), offset_(offset), size_(size) {}

bool Yesdb::Get(const std::string key, std::string &value) {
  if (fd_ == -1) {
    PLOG_DEBUG << "file don't open.\n";
    return false;
  }

  if (key_dir.find(key) == key_dir.end()) {
    PLOG_DEBUG << str_format("db don't exist the key = %s.\n", key.data());
    return false;
  }
  Entry entry = key_dir[key];
  return ReadData(entry, value);
}

bool Yesdb::Flush() {
  int res = write(fd_, data_.data(), data_.size());
  if (res == -1) {
    PLOG_DEBUG << "write error";
    return false;
  }
  PLOG_DEBUG << str_format("success write %d bytes\n", res);
  return true;
}

bool Yesdb::Sync() {
  int ret = fsync(fd_);
  return ret == -1 ? false : true;
}

bool Yesdb::Close() {
  close(fd_);
  return true;
}

bool Yesdb::ReadData(Entry entry, std::string &value) {
  if (entry.fd_ == -1) {
    PLOG_DEBUG << "file don't open.\n";
    return false;
  }
  char buffer[BUFSIZ];

  while (true) {
    lseek(entry.fd_, entry.offset_, SEEK_SET);
    memset(buffer, 0, sizeof(buffer));
    int n = read(entry.fd_, buffer, sizeof(buffer));
    if (n == -1) {
      if (errno == EINTR) {
        continue;
      }
      return false;
    }
    if (n > 0) {
      // deserialize
      int pos = 0;
      uint32_t tstamp;
      uint32_t uint32_sz = sizeof(uint32_t);
      uint32_t checksum;
      memcpy(&checksum, buffer + pos, uint32_sz);
      pos += uint32_sz;
      memcpy(&tstamp, buffer + pos, uint32_sz);
      pos += uint32_sz;
      uint32_t key_sz, value_sz;
      memcpy(&key_sz, buffer + pos, uint32_sz);
      pos += uint32_sz;
      memcpy(&value_sz, buffer + pos, uint32_sz);
      pos += uint32_sz;

      std::string key;
      char temp_key[BUFSIZ];
      char temp_value[BUFSIZ];
      memcpy(temp_key, buffer + pos, key_sz);
      pos += key_sz;
      memcpy(temp_value, buffer + pos, value_sz);
      pos += value_sz;
      uint32_t new_checksum =
          crc32_checksum(buffer + uint32_sz, pos - uint32_sz);
      assert(new_checksum == checksum);
      value = std::string(temp_value);
      return true;
    }
  }
}

bool Yesdb::Serialize() { return false; }

bool Yesdb::Deserialize() { return false; }

bool Yesdb::Compress(const std::string originalData,
                     std::vector<char> &cmpr_data, int &cmpr_size) {
  size_t compressedBufferSize = ZSTD_compressBound(originalData.size());
  std::vector<char> compressedBuffer(compressedBufferSize);

  size_t compressedSize =
      ZSTD_compress(compressedBuffer.data(), compressedBuffer.size(),
                    originalData.data(), originalData.size(), ZSTD_maxCLevel());
  if (ZSTD_isError(compressedSize)) {
    std::cerr << "Compression error: " << ZSTD_getErrorName(compressedSize)
              << std::endl;
    return false;
  }
  cmpr_data = compressedBuffer;
  cmpr_size = compressedSize;
  return true;
}

bool Yesdb::Decompress(std::vector<char> &cmpr_data, std::string &decmpr_data,
                       const int cmpr_size, const int org_size) {
  std::vector<char> decompressedBuffer(org_size);
  size_t decompressedSize =
      ZSTD_decompress(decompressedBuffer.data(), decompressedBuffer.size(),
                      cmpr_data.data(), cmpr_size);

  if (ZSTD_isError(decompressedSize)) {
    std::cerr << "Decompression error: " << ZSTD_getErrorName(decompressedSize)
              << std::endl;
    return false;
  }
  decmpr_data = std::move(decompressedBuffer.data());
  return true;
}

} // namespace yesdb
