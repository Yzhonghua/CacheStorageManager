#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>

const size_t FRAME_NUM = 1024;
const size_t PAGE_SIZE = 4096;
const std::string DB_FILE_NAME = "./target/data.dbf";

enum class ReplaceChoice {
    LRU,
    CLOCK
};

using FrameID = size_t;
using PageID = size_t;
using Data = std::array<uint8_t, PAGE_SIZE>;

class Config {
 public:
  static Config* getInstance() {
    static Config config;
    return &config;
  }
  void init(int argc, char* argv[]) {
    if (argc != 3) {
        throw std::invalid_argument("Usage: ./cache_storage_manager --[LRU/CLOCK] [file_path]");
    }

    if (argv[1] == "--LRU") {
        m_choice = ReplaceChoice::LRU;
    } else if (argv[1] == "--CLOCK") {
        m_choice = ReplaceChoice::CLOCK;
    } else {
        throw std::invalid_argument("Usage: ./cache_storage_manager --[LRU/CLOCK] [file_path]");
    }

    m_file_path = agrv[2];
  }

 private:
    ReplaceChoice m_choice;
    std::string m_file_path;
}

#endif  // _CONFIG_H_
