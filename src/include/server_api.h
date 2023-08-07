#pragma once

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <utility>
#include <string>

namespace yesdb {


class Yesdb {
   public:
    Yesdb(std::string filename);
    ~Yesdb();
    bool Open();
    void Close();
    // 插入
    void Put(const char *key, const char *value);
   
   private:
    
    std::string filename_;
    int fd_;
    std::unordered_map<uint64_t, std::string> key_dir; // 使用art作为key目录查询
    std::unordered_map<uint64_t, std::string> open_files;// key-->File
    uint64_t active_file_id; // 活跃的文件
    size_t size;
    bool is_opened;
    std::shared_mutex mutex;
    inline static const char *TOMBSTONE = "YESDB_TOMBSTONE_VALUE";
    inline static const char *DATA_FILE_EXTENTION = ".data";
    inline static const char *HINT_FILE_EXTENTION = ".hint";
    inline static const char *TEMP_FILE_EXTENTION = ".tmp";
    inline static const char *LOCK_FILE = ".lock";
};

}  // namespace yesdb