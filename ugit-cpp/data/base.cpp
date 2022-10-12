/**
 * @file base.cpp
 * @author shejialuo
 *
 */

#include "base.hpp"

#include "data.hpp"
#include "err.hpp"
#include "spdlog/spdlog.h"
#include "util.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

constexpr int INFO_FIELD_NUM = 3;

static void readTreeRecursive(std::string treeID,
                              std::string path,
                              std::unordered_map<std::string, std::string> &results);

static void emptyCurrentDirectory();

/**
 * @brief recursively call `hashObject` for each file
 * and write tree objects using `hashObject`
 *
 * @param directory
 * @return std::string object id for tree
 */
std::string ugit::writeTree(std::string directory) {
  using namespace std::filesystem;
  std::vector<std::tuple<std::string, std::string, std::string>> info{};
  // Here, we use `directory_iterator` to gracefully
  // iterate the directories.
  for (auto const &entry : directory_iterator{directory}) {
    std::string objectID{};
    std::string type{};
    // We should ignore the ".ugit" path, actually, we could do
    // better here, maybe we could let use create a `.ugitignore`
    // file for us to ignore some specified.
    if (entry.path().filename() == ".ugit") {
      continue;
    }
    if (entry.is_regular_file()) {
      const std::vector<uint8_t> data = ugit::readBinaryFromFile(entry.path().string());
      objectID = ugit::hashObject(data);
      type = "blob";
    } else if (entry.is_directory()) {
      objectID = writeTree(entry.path().string());
      type = "tree";
    }

    if (!objectID.empty()) {
      info.push_back(std::make_tuple(type, objectID, entry.path().filename().string()));
    }
  }

  // sort the tuple
  sort(info.begin(), info.end());
  std::string results{};
  for (auto &&i : info) {
    results += std::get<0>(i) + " " + std::get<1>(i) + " " + std::get<2>(i) + "\n";
  }
  const std::vector<uint8_t> data{results.cbegin(), results.cend()};
  return ugit::hashObject(data, "tree");
}

/**
 * @brief read the treeID recursively and writes the content to
 * the workspace.
 *
 * @param treeID tree object ID
 */
void ugit::readTree(std::string treeID) {
  using namespace std::filesystem;
  emptyCurrentDirectory();
  std::unordered_map<std::string, std::string> pathObjectIDMap{};
  readTreeRecursive(treeID, ".", pathObjectIDMap);
  for (auto &&p : pathObjectIDMap) {
    path file{p.first};
    // Because ofstream cannot automatically create  new directories
    // Here we should create the new directory
    if (!exists(file.parent_path())) {
      create_directories(file.parent_path());
    }
    std::ofstream os{p.first, std::ios::trunc | std::ios::binary};
    if (!os.is_open()) {
      spdlog::error("could not open {}, the parent directories may not be created", p.first);
      exit(static_cast<int>(ugit::Error::FileNotExist));
    }
    std::string objectContent = ugit::getObject(p.second);
    os.write(objectContent.c_str(), objectContent.size());
    os.close();
  }
}

/**
 * @brief auxiliary function for reading trees, it is like
 * iterating the directory.
 *
 * @param treeID tree object id
 * @param path the base path
 * @param results
 */
static void readTreeRecursive(std::string treeID,
                              std::string path,
                              std::unordered_map<std::string, std::string> &results) {
  std::istringstream treeStream{std::move(ugit::getObject(treeID, "tree"))};
  std::string oneLineRecord{};
  // We get the record line by line
  while (std::getline(treeStream, oneLineRecord)) {
    std::istringstream oneLineStream{std::move(oneLineRecord)};
    std::string infos[INFO_FIELD_NUM];
    for (int i = 0; i < INFO_FIELD_NUM; ++i) {
      oneLineStream >> infos[i];
    }
    // It is really a ugly way.
    std::string absolutePath = path + "/" + infos[2];

    if (infos[0] == "blob") {
      results[absolutePath] = infos[1];
    } else if (infos[0] == "tree") {
      // We need to read tree recursively
      readTreeRecursive(infos[1], absolutePath, results);
    } else {
      spdlog::error("unkown type {}", infos[0]);
      exit(static_cast<int>(ugit::Error::TypeError));
    }
  }
}

/**
 * @brief Delete all the files in the current directories
 *
 */
static void emptyCurrentDirectory() {
  using namespace std::filesystem;
  for (auto const &entry : directory_iterator{"."}) {
    if (entry.path().filename() == ".ugit") {
      continue;
    }
    remove_all(entry);
  }
}