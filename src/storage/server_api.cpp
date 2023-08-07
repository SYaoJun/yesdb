#include <ctime>
#include <filesystem>
#include <fstream>
#include <unordered_set>
#include <iostream>
#include <unistd.h>
#include "include/server_api.h"

namespace yesdb {
namespace fs = std::filesystem;

Yesdb::Yesdb(std::string filename)
    :filename_(filename),
      active_file_id{0}, size{0}, is_opened{false} {}

Yesdb::~Yesdb() {}



bool Yesdb::Open() {
        fd_ =open("D:\\a.txt",O_RDWR);
 
        if(fd_==-1){
 
        printf("can not open the file\n");
 
      return false;
 
   }
 
   printf("successful to open the file\n");
    
    return true;
    }
}



} // namespace yesdb
