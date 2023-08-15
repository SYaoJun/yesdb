#include <cstddef>
#include <ctime>
#include <fcntl.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
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

class Yesdb {
public:
  Yesdb(std::string filename);
  ~Yesdb();
  bool Open();
  bool Close();

  bool Put(const std::string key, const std::string value);
  bool Get(const std::string key, std::string &value);
  bool Flush();

  bool Sync();
  bool Compress(const std::string org_data, std::vector<char> &cmpr_data,
                int &cmpr_size);
  bool Decompress(std::vector<char> &cmpr_data, std::string &decmpr_data,
                  const int cmpr_size, const int org_size);

private:
  std::string filename_;
  int fd_;
  int offset_;
  std::string data_;
  std::unordered_map<std::string, Entry> key_dir;
  std::shared_mutex mutex;
  inline static const char *TOMBSTONE = "YESDB_TOMBSTONE_VALUE";

  bool ReadData(Entry entry, std::string &value);
  bool Serialize();
  bool Deserialize();
};
} // namespace yesdb
