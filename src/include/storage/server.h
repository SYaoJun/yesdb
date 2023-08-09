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
        bool Close();
        // 插入
        bool Put(const std::string key, const std::string value);
        bool Get(const std::string key, std::string &value);
        bool Flush();
        bool Sync();

    private:
        std::string filename_;
        int fd_;
        std::string data_;
        std::unordered_map<uint64_t, Entry> key_dir;          
        std::unordered_map<uint64_t, std::string> open_files; 
        uint64_t active_file_id;                              
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