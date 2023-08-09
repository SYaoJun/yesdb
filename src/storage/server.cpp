
#include "storage/server.h"
#include "common/time.h"
/*
    +-------+--------+--------+----------+-----+-------+--------+
    | crc32 | tstamp | key_sz | value_sz | key | value | offset |
    +-------+--------+--------+----------+-----+-------+--------+
    */
namespace yesdb {
    namespace fs = std::filesystem;

    Yesdb::Yesdb(std::string filename)
            : filename_(filename),
              active_file_id{0}, size{0}, is_opened{false} {}

    Yesdb::~Yesdb() {}

    bool Yesdb::Open() {
        fd_ = open(filename_.data(), O_RDWR);
        if (fd_ == -1) {
            printf("can not open the file\n");
            return false;
        }

        printf("successful to open the file\n");
        return true;
    }

    bool Yesdb::Put((const std::string key, const std::string value) {
        if (fd_ == -1) {
            printf("file don't open.\n");
            return false;
        }
        // std::unique_lock lock(mutex);
        // bool is_new = false;
        // if (key_dir.find(key) == key_dir.end())
        // {
        //   is_new = true;
        // }
        // uint32_t key_sz = strlen(key);
        // uint32_t value_sz = strlen(value);
        // uint32_t tuple_sz = 4 * sizeof(uint32_t) + key_sz + value_sz;
        // char buffer[BUFSIZ];
        // // calculate checksum
        // int pos = 0;
        // uint32_t tstamp = timestamp();
        // uint32_t uint32_sz = sizeof(uint32_t);
        // memcpy(buffer + pos, &tstamp, uint32_sz);
        // pos += uint32_sz;
        // memcpy(buffer + pos, &key_sz, uint32_sz);
        // pos += uint32_sz;
        // memcpy(buffer + pos, &key_sz, uint32_sz);
        // pos += uint32_sz;
        // memcpy(buffer + pos, key, key_sz);
        // pos += key_sz;
        // memcpy(buffer + pos, key, key_sz);
        // pos += value_sz;
        // uint32_t checksum = crc32_checksum(buffer, pos);

        // char sup_buffer[BUFSIZ];
        // uint32_t new_pos = 0;
        // memcpy(sup_buffer + new_pos, &checksum, uint32_sz);
        // new_pos += uint32_sz;
        // memcpy(sup_buffer + new_pos, buffer, pos);
        // new_pos += pos;

        // // 如果一次写入不完怎么办？
        // int ret = write(fd_ + offset_, sup_buffer, new_pos);
        // if (ret < 0)
        // {
        //   printf("write failed.\n");
        //   return false;
        // }
        // Entry entry(fd_, offset_, new_pos);
        // offset_ += new_pos;
        // key_dir[key] = entry;
        return true;
    }

    Entry::Entry(int fd, int offset, int size) : fd_(fd), offset_(offset),
                                                 size_(size) {
    }

    bool Yesdb::Get(const std::string key, std::string &value) {
        if (fd_ == -1) {
            printf("file don't open.\n");
            return false;
        }

        if (key_dir.find(key) == key_dir.end())
        {
          printf("db don't exist the key = %s.\n", key);
          return false;
        }
        value = ":)";
        return true;
    }

    bool Yesdb::Flush() {
        int res = write(fd_, data_.data(), data_.size());
        if (res == -1) {
            printf("write error");
            return false;
        }
        printf("success write %d bytes\n", res);
        return true;
    }

    bool Yesdb::Sync() {
        Flush();
        int ret = fsync(fd_);
        return ret == -1 ? false: true;
    }

    bool Yesdb::Close(){
        close(fd_);
        return true;
    }
} // namespace yesdb
