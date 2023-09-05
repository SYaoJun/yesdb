#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstddef>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace yesdb {
class Entry {
   public:
    Entry() = default;
    Entry(int fd, int offset, int size_);
    int fd_;
    int offset_;
    int size_;
};

class DBImpl {
   public:
    DBImpl(std::string filename);
    ~DBImpl();
    bool Open();
    bool Close();

    bool Put(const std::string key, const std::string value);
    bool Get(const std::string key, std::string &value);
    bool Flush();

    bool Sync();
    // bool Compress(const std::string org_data, std::vector<char> &cmpr_data, int &cmpr_size);
    // bool Decompress(std::vector<char> &cmpr_data, std::string &decmpr_data, const int cmpr_size, const int org_size);

    void LoadIndex();
    void AutoMerge();

   private:
    std::string filename_;
    int fd_;
    int offset_;
    std::string data_;
    int max_file_no_;
    std::unordered_map<std::string, Entry> key_dir;
    std::shared_mutex mutex;
    inline static const char *TOMBSTONE = "yesdb_TOMBSTONE_VALUE";

    bool ReadData(Entry entry, std::string &value);
    bool Serialize();
    bool Deserialize();
};

enum Option { PUT = 0, GET, DELTE, SCAN };
}  // namespace yesdb
