/**
 * @file data.cpp
 * @author shejialuo
 *
 */

#include "data.hpp"

#include "err.hpp"
#include "spdlog/spdlog.h"
#include "util.hpp"

#include <algorithm>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string_view>
#include <vector>

constexpr std::string_view GIT_DIR = ".ugit";

void ugit::initialization() {
  using namespace std::filesystem;
  path dir{GIT_DIR};
  if (!create_directory(dir)) {
    spdlog::error("create directory {} failed", GIT_DIR);
    exit(static_cast<int>(ugit::Error::CraeteFileError));
  }
  spdlog::info("create directorty {}", GIT_DIR);
  path object{"objects"};
  path objectDir = dir / object;
  if (!create_directories(objectDir)) {
    spdlog::error("create diretory {} failed", objectDir.string());
    exit(static_cast<int>(ugit::Error::CraeteFileError));
  }
  spdlog::info("create directory {}", objectDir.string());
}

/**
 * @brief Read the data of the file to generate its sha1sum
 * And create the files named `sha1sum` whose content is the
 * data of the file. Well, just a mapping.
 *eturn ugit::sha1sumHex(data);
 * @param file the path of the file
 */
std::string ugit::hashObject(std::string file) {
  using namespace std::filesystem;

  // First, we need to read the content of the file as the binary
  // We should do some check for robust
  if (!exists(file)) {
    spdlog::error("{} does not exist", file);
    exit(static_cast<int>(ugit::Error::FileNotExist));
  }
  std::ifstream fs{file, std::ios::binary};
  const std::vector<uint8_t> data{std::istreambuf_iterator<char>(fs), {}};
  fs.close();

  // Second, calculate the sha1sumHexValue
  std::string objectID = ugit::sha1sumHex(data);

  // Now we need to write the binary contents to the file
  path objectHashFile = path{GIT_DIR} / path{"objects"} / path{objectID};
  std::ofstream os{objectHashFile.string(), std::ios::binary | std::ios::trunc};
  os.write(reinterpret_cast<const char *>(&data[0]), data.size());
  os.close();
  return objectID;
}

/**
 * @brief Get the content for the specified object id
 *
 * @param object object id
 */
std::string ugit::getObject(std::string object) {
  using namespace std::filesystem;
  path objectHashFile = path{GIT_DIR} / path{"objects"} / path{object};
  std::ifstream fs{objectHashFile.string(), std::ios::binary};
  std::string result{std::istreambuf_iterator<char>(fs), {}};
  fs.close();
  return result;
}
