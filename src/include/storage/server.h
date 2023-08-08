#include <cstddef>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <utility>
#include <string>
#include <fcntl.h>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <unordered_set>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>    
#include <sys/stat.h>    
#include <fcntl.h>
namespace yesdb
{
    class Entry
    {
        Entry(int fd, int offset, int size_);
        int fd_;
        int offset_;
        int size_;
    };

    class Yesdb
    {
    public:
        Yesdb(std::string filename);
        ~Yesdb();
        bool Open();
        void Close();
        // 插入
        bool Put(const char *key, const char *value);
        bool Get(const char *key, char *value);

    private:
        std::string filename_;
        int fd_;
        std::unordered_map<uint64_t, Entry> key_dir;          // 使用art作为key目录查询
        std::unordered_map<uint64_t, std::string> open_files; // key-->File
        uint64_t active_file_id;                              // 活跃的文件
        size_t size;
        bool is_opened;
        uint32_t offset_;
        std::shared_mutex mutex;
        inline static const char *TOMBSTONE = "YESDB_TOMBSTONE_VALUE";
        inline static const char *DATA_FILE_EXTENTION = ".data";
        inline static const char *HINT_FILE_EXTENTION = ".hint";
        inline static const char *TEMP_FILE_EXTENTION = ".tmp";
        inline static const char *LOCK_FILE = ".lock";
    };

    

} // namespace yesdb