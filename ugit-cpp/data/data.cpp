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

static std::tuple<std::string, ugit::RefContainer> getRefInternal(std::string ref, bool deref);

/**
 * @brief initialize the ugit application, create the
 * `.ugit` and `.ugit/objects` directories.
 *
 */
void ugit::initializationDirectories() {
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
 * data of the file. Well, just a mapping (content addressing).
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
 * @param objectID object id
 * @param type the specified type
 */
std::string ugit::getObject(std::string objectID, std::string type) {
  using namespace std::filesystem;
  path objectHashFile = path{GIT_DIR} / path{"objects"} / path{objectID};
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
 * @brief update the reference value to `ref`.
 *
 * @param ref reference name
 * @param value the wrapped value RefContainer
 * @param deref whether to dereference the symbolic reference
 */
void ugit::updateRef(std::string ref, ugit::RefContainer value, bool deref) {
  using namespace std::filesystem;

  // find the reference path, which should point to
  // the actual object id.
  ref = std::get<0>(getRefInternal(ref, deref));

  std::string refValue{};
  if (value.symbolic) {
    refValue = "ref: " + value.value;
  } else {
    refValue = value.value;
  }

  path refPath = path{GIT_DIR} / path{ref};
  // We need to create directories if they does not exist
  create_directories(refPath.parent_path());

  if (!ugit::writeBinaryToFile(refPath.string(), refValue.c_str(), refValue.size())) {
    spdlog::error("cannot open {} for writing", refPath.string());
    exit(static_cast<int>(ugit::Error::OpenFileError));
  }
}

/**
 * @brief To get the wrapped tuple ref value
 *
 * @param ref reference name
 * @param deref whether dereference refs
 * @return wrapped tuple ref value RefContainer
 */
ugit::RefContainer ugit::getRef(std::string ref, bool deref) { return std::get<1>(getRefInternal(ref, deref)); }

/**
 * @brief Use `recursive_directory_iterator` to find the `.ugit/refs`
 * to produce the `unordered_map`.
 *
 * @param refMap
 * @param deref
 */
void ugit::iterateRefs(std::unordered_map<std::string, ugit::RefContainer> &refMap, bool deref) {
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
    refMap[ref.string()] = ugit::getRef(ref.string(), deref);
  }
}

/**
 * @brief A helper function to get the internal object id or
 * get the symbolic value.
 *
 * @param ref reference name
 * @return std::tuple<std::string, ugit::RefContainer>
 *         1. std::string the reference name
 *         2. ugit::RefContainer a container with contents and indicator whether it is symbolic
 */
static std::tuple<std::string, ugit::RefContainer> getRefInternal(std::string ref, bool deref) {
  using namespace std::filesystem;
  path file = path{GIT_DIR} / path{ref};

  // When we are at the root, there is no reference, we just return
  // its content with empty string.
  if (!exists(file)) {
    return std::make_tuple(ref, ugit::RefContainer{});
  }

  std::string refContent = ugit::readStringFromFile(file.string());
  // We need to recursively deal with symbolic references
  bool symbolic = !refContent.empty() && refContent.substr(0, 4) == "ref:";
  if (symbolic) {
    refContent = refContent.substr(5);
    // If we want to dereference the symbolic, we just go on.
    if (deref) {
      return getRefInternal(refContent, deref);
    }
  }
  return std::make_tuple(ref, ugit::RefContainer{symbolic, refContent});
}
