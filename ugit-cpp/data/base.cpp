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

static bool isBranch(std::string branchName);

/**
 * @brief Initialization the ugit application.
 *
 */
void ugit::initialization() {
  using namespace std::filesystem;
  ugit::initializationDirectories();
  path master = path{"refs"} / path{"heads"} / path{"master"};
  ugit::updateRef("HEAD", ugit::RefContainer{true, master.string()});
}

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
    // Because ofstream cannot automatically create new directories
    // Here we should create the new directory
    if (!exists(file.parent_path())) {
      create_directories(file.parent_path());
    }
    std::string objectContent = ugit::getObject(p.second);
    if (!ugit::writeBinaryToFile(p.first, objectContent.c_str(), objectContent.size())) {
      spdlog::error("could not open {}, the parent directories may not be created", p.first);
      exit(static_cast<int>(ugit::Error::FileNotExist));
    }
  }
}

/**
 * @brief Create 'commit' object and write the oid and parent
 * oid. Also write the object id to the HEAD to indicate where
 * we are.
 *
 * @param message
 * @return commit object id
 */
std::string ugit::commit(std::string message) {
  std::string commitContent = "tree " + ugit::writeTree() + "\n";
  // Get the current commit object id
  std::string headContent = ugit::getRef("HEAD").value;
  if (!headContent.empty()) {
    commitContent += "parent " + headContent + "\n";
  }
  commitContent += "\n" + message + "\n";
  const std::vector<uint8_t> data{commitContent.cbegin(), commitContent.cend()};
  std::string commitID = ugit::hashObject(data, "commit");
  ugit::updateRef("HEAD", ugit::RefContainer{false, commitID});
  return commitID;
}

/**
 * @brief Parse the commit file to generate the
 * CommitMessage
 *
 * @param commitID
 * @return CommitMessage objects
 */
ugit::CommitMessage ugit::getCommit(std::string commitID) {
  std::string treeID{}, parentCommitID{}, key{}, objectID{}, commitMessage{};

  std::istringstream commitStream{std::move(ugit::getObject(commitID, "commit"))};
  std::string oneLineRecord{};
  // when we reading the empty line, we get the delimeter
  while (std::getline(commitStream, oneLineRecord) && !oneLineRecord.empty()) {
    std::istringstream oneLineStream{oneLineRecord};

    oneLineStream >> key;
    oneLineStream >> objectID;
    if (key == "tree") {
      treeID = objectID;
    } else if (key == "parent") {
      parentCommitID = objectID;
    } else {
      spdlog::error("{} is not valid", key);
      exit(static_cast<int>(ugit::Error::TypeError));
    }
  }

  // We need to just read until the end of the string,
  // which should be EOF, -1, however, we need a char to
  // represent it, so use `\xff`.
  std::getline(commitStream, commitMessage, '\xff');

  return ugit::CommitMessage{treeID, parentCommitID, commitMessage};
}

/**
 * @brief Populate the working directory with the content of the
 * commit and move HEAD to point to it
 *
 * @param name could be commit object ID or could be a name which
 * represents the tag and the branch name
 */
void ugit::checkout(std::string name) {
  auto commit = ugit::getCommit(ugit::resolveObjectID(name));
  ugit::readTree(commit.treeID);

  ugit::RefContainer HEAD{};
  if (isBranch(name)) {
    HEAD.symbolic = true;
    HEAD.value = "refs/heads/" + name;
  } else {
    HEAD.symbolic = false;
    HEAD.value = name;
  }

  ugit::updateRef("HEAD", HEAD, false);
}

/**
 * @brief create tag, just creates a reference to point to
 * one of the object ID. i.e., alias.
 *
 * @param tagName
 */
void ugit::createTag(std::string tagName, std::string objectID) {
  using namespace std::filesystem;
  path refPath = path{"refs"} / path{"tags"} / path{tagName};
  ugit::updateRef(refPath.string(), ugit::RefContainer{false, objectID});
}

/**
 * @brief get object ID from symbolic name, if it is not, just
 * return itself , which should be raw object hash id.
 *
 * @param name the symbolic name
 * @return std::string the raw object hash id
 */
std::string ugit::resolveObjectID(std::string name) {
  using namespace std::filesystem;

  // If we accept the empty name, we just use HEAD
  // as the default value
  if (name.empty()) {
    name = "HEAD";
  }
  path refs[] = {
      name,
      path{"refs"} / path{name},
      path{"refs"} / path{"tags"} / path{name},
      path{"refs"} / path{"heads"} / path{name},
  };
  for (auto ref : refs) {
    std::string id = ugit::getRef(ref.string()).value;
    if (!id.empty())
      return id;
  }

  return name;
}

/**
 * @brief call `updateRef`
 *
 * @param branchName the branch name
 * @param commitID
 */
void ugit::createBranch(std::string branchName, std::string commitID) {
  using namespace std::filesystem;
  path refPath = path{"refs"} / path{"heads"} / path{branchName};
  ugit::updateRef(refPath.string(), ugit::RefContainer{false, commitID});
}

/**
 * @brief get the branch name from the HEAD, if the HEAD is
 * detached return empty string.
 *
 * @return std::string branch name
 */
std::string ugit::getBranchName() {
  using namespace std::filesystem;
  auto head = ugit::getRef("HEAD", false);
  if (!head.symbolic) {
    return {};
  }

  path ref = path{"refs"} / path{"heads"};

  return relative(head.value, ref).string();
}

/**
 * @brief return all the branches
 *
 * @return std::vector<std::string>
 */
std::vector<std::string> ugit::getBranchNames() {
  using namespace std::filesystem;
  path refPath = path{"refs"} / path{"heads"};
  std::unordered_map<std::string, ugit::RefContainer> refMaps{};
  ugit::iterateRefs(refMaps, true, refPath.string());
  std::vector<std::string> branchNames{};
  for (const auto &ref : refMaps) {
    branchNames.push_back(relative(ref.first, refPath));
  }
  return branchNames;
}

/**
 * @brief move HEAD to an commit ID
 *
 * @param commitID
 */
void ugit::reset(std::string commitID) { ugit::updateRef("HEAD", ugit::RefContainer{false, commitID}); }

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

/**
 * @brief check whether the name is a branch
 *
 * @param branchName th
 * @return true if it is a symbolic ref of branch
 * @return false if not
 */
static bool isBranch(std::string branchName) {
  using namespace std::filesystem;
  path branchPath = path{"refs"} / path{"heads"} / path{branchName};
  return !ugit::getRef(branchPath.string()).value.empty();
}
