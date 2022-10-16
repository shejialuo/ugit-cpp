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

  // Here, I just use a space to indicate the delimiter, actually
  // it is not a good design, just for simplicity.
  std::string content = type + " " + std::string{data.cbegin(), data.cend()};
  if (!ugit::writeBinaryToFile(objectHashFile.string(), content.c_str(), content.size())) {
    spdlog::error("{} could not be opened, there may be no ugit repository.", objectHashFile.string());
    exit(static_cast<int>(ugit::Error::OpenFileError));
  }
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
  std::string result = ugit::readStringFromFile(objectHashFile.string());

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
 * @brief update reference
 *
 * @param ref reference name
 * @param commitID
 */
void ugit::updateRef(std::string ref, std::string objectID) {
  using namespace std::filesystem;
  path refPath = path{GIT_DIR} / path{ref};
  create_directories(refPath.parent_path());
  if (!ugit::writeBinaryToFile(refPath.string(), objectID.c_str(), objectID.size())) {
    spdlog::error("cannot open {} for writing", refPath.string());
    exit(static_cast<int>(ugit::Error::OpenFileError));
  }
}

/**
 * @brief return the ref commit object ID
 *
 * @param ref reference name
 * @return std::string
 */
std::string ugit::getRef(std::string ref) {
  using namespace std::filesystem;
  path file = path{GIT_DIR} / path{ref};

  // When we are at the root, there is no HEAD FILE, we just return
  // an empty string
  if (!exists(file)) {
    return {};
  }
  std::string refContent = ugit::readStringFromFile(file.string());
  return refContent;
}

/**
 * @brief Use `recursive_directory_iterator` to find the `.ugit/refs`
 * to produce the `unordered_map`.
 *
 * @param refMap
 */
void ugit::iterateRefs(std::unordered_map<std::string, std::string> &refMap) {
  using namespace std::filesystem;

  std::vector<path> refs{"HEAD"};

  path refDir = path{GIT_DIR} / path{"refs"};
  if (exists(refDir)) {
    for (auto const &entry : recursive_directory_iterator{refDir}) {
      if (entry.is_regular_file()) {
        refs.push_back(relative(entry.path(), path{GIT_DIR}));
      }
    }
  }
  for (auto &ref : refs) {
    refMap[ref.string()] = ugit::getRef(ref.string());
  }
}
