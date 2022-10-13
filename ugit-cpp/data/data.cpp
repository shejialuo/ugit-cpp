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
    exit(static_cast<int>(ugit::Error::CreateFileError));
  }
  spdlog::info("create directory {}", GIT_DIR);
  path object{"objects"};
  path objectDir = dir / object;
  if (!create_directories(objectDir)) {
    spdlog::error("create directory {} failed", objectDir.string());
    exit(static_cast<int>(ugit::Error::CreateFileError));
  }
  spdlog::info("create directory {}", objectDir.string());
}

/**
 * @brief From binary data to generate its sha1sum
 * And create the files named `sha1sum` whose content is the
 * data of the file. Well, just a mapping.
 *
 * @param data the binary data of the reading content.
 * @param type the specified type.
 */
std::string ugit::hashObject(const std::vector<uint8_t> &data, std::string type) {
  using namespace std::filesystem;

  // Calculate the object id
  std::string objectID = ugit::sha1sumHex(data);

  // Now we need to write the binary contents to the file
  path objectHashFile = path{GIT_DIR} / path{"objects"} / path{objectID};
  std::ofstream os{objectHashFile.string(), std::ios::binary | std::ios::trunc};
  if (!os.is_open()) {
    spdlog::error("{} could not be opened, there may be no ugit repository.", objectHashFile.string());
    exit(static_cast<int>(ugit::Error::OpenFileError));
  }
  // Here, I just use a space to indicate the delimiter, actually
  // it is not a good design, just for simplicity.
  std::string typeIndicator = type + " ";
  os.write(typeIndicator.c_str(), typeIndicator.size());
  os.write(reinterpret_cast<const char *>(&data[0]), data.size());
  os.close();
  return objectID;
}

/**
 * @brief Get the content for the specified object id
 *
 * @param object object id
 * @param type the specified type
 */
std::string ugit::getObject(std::string object, std::string type) {
  using namespace std::filesystem;
  path objectHashFile = path{GIT_DIR} / path{"objects"} / path{object};
  if (!exists(objectHashFile)) {
    spdlog::error("{} does not exist, there may be no ugit repository "
                  "or your object id is not correct.",
                  objectHashFile.string());
    exit(static_cast<int>(ugit::Error::FileNotExist));
  }
  std::ifstream fs{objectHashFile.string(), std::ios::binary};
  std::string result{std::istreambuf_iterator<char>(fs), {}};
  fs.close();

  // Here, we need to find the first space.
  std::string typeFromFile{};
  ugit::getTypeAndRemoveType(typeFromFile, result);
  if (typeFromFile != type) {
    spdlog::error("{} is no equal to actual {}. Check the type", type, typeFromFile);
    exit(static_cast<int>(ugit::Error::TypeNotEqual));
  }

  return result;
}

/**
 * @brief write the commit object id to the HEAD
 *
 * @param commitID
 */
void ugit::setHead(std::string commitID) {
  using namespace std::filesystem;
  path file = path{GIT_DIR} / path{"HEAD"};
  std::ofstream os{file.string(), std::ios::trunc | std::ios::binary};
  if (!os.is_open()) {
    spdlog::error("cannot open {} for writing", file.string());
    exit(static_cast<int>(ugit::Error::OpenFileError));
  }
  os.write(commitID.c_str(), commitID.size());
  os.close();
}

/**
 * @brief return the current commit object ID
 *
 * @return std::string
 */
std::string ugit::getHead() {
  using namespace std::filesystem;
  path file = path{GIT_DIR} / path{"HEAD"};
  // When we are at the root, there is no HEAD FILE, we just return
  // an empty string
  if (!exists(file)) {
    return {};
  }
  std::ifstream is{file.string(), std::ios::binary};
  if (!is.is_open()) {
    spdlog::error("cannot open {} for reading", file.string());
    exit(static_cast<int>(ugit::Error::OpenFileError));
  }
  std::string headContent{std::istreambuf_iterator<char>(is), {}};
  is.close();
  return headContent;
}
