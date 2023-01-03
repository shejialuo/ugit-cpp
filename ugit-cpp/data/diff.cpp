/**
 * @file diff.cpp
 * @author shejialuo
 *
 */

#include "diff.hpp"

#include "data.hpp"
#include "spdlog/spdlog.h"
#include "util.hpp"

#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>

static std::string diffBlobs(std::string objectID, std::string objectParentID, std::string path = "blob");

/**
 * @brief diff the tree 1 and tree 2
 *
 * @param tree tree content
 * @param treeParent the parent of `tree`'s content
 * @return std::string
 */
std::string ugit::diffTrees(const std::string &tree, const std::string &treeParent) {
  std::string result{};
  std::unordered_map<std::string, std::pair<std::string, std::string>> pathToObjectIDs{};

  parseTreeContent(tree, pathToObjectIDs, 0);
  parseTreeContent(treeParent, pathToObjectIDs, 1);

  for (auto &pathToObjectID : pathToObjectIDs) {
    const std::string &path = pathToObjectID.first;
    const std::string &now = pathToObjectID.second.first;
    const std::string &parent = pathToObjectID.second.second;

    // Here, we do not recursively descend into the tree, which
    // is not realistic. However, for simplicity make our life
    // easier.
    if (now != parent) {
      result += diffBlobs(now, parent);
    }
  }

  return result;
}

/**
 * @brief parse the tree content, auxilary function
 *
 * @param tree tree content
 * @param pathToObjectIDs
 */
void parseTreeContent(const std::string &tree,
                      std::unordered_map<std::string, std::pair<std::string, std::string>> &pathToObjectIDs,
                      int index) {
  std::stringstream treeContent{tree};
  std::string lineContent{}, type{}, objectID{}, path{};
  while (std::getline(treeContent, lineContent)) {
    std::stringstream oneLineRecord{std::move(lineContent)};
    oneLineRecord >> type;
    oneLineRecord >> objectID;
    oneLineRecord >> path;

    // We do not care about recursively descending into the tree
    // If you wan to descend into the tree
    if (type == "tree") {
      continue;
    }

    if (index == 0) {
      if (pathToObjectIDs.count(path)) {
        pathToObjectIDs[path].first = objectID;
      } else {
        pathToObjectIDs[path] = {objectID, ""};
      }
    } else {
      if (pathToObjectIDs.count(path)) {
        pathToObjectIDs[path].second = objectID;
      } else {
        pathToObjectIDs[path] = {"", objectID};
      }
    }
  }
}

/**
 * @brief use unix `diff` to get the difference of two object id
 *
 * @param objectID
 * @param objectParentID
 * @param path
 * @return std::string
 */
static std::string diffBlobs(std::string objectID, std::string objectParentID, std::string path) {
  // This is dangerous, however, make life easier.
  std::string tempName = "/tmp/a";
  std::string tempNameParent = "/tmp/b";

  std::string content{};
  std::string contentParent{};
  if (!objectID.empty()) {
    content = ugit::getObject(objectID);
  }
  if (!objectParentID.empty()) {
    contentParent = ugit::getObject(objectParentID);
  }

  std::ofstream out{tempName, std::ios::trunc};
  out.write(content.c_str(), content.size());
  out.close();

  std::ofstream outParent{tempNameParent, std::ios::trunc};
  outParent.write(contentParent.c_str(), content.size());
  outParent.close();

  std::string command = "diff -a --unified --show-c-function --label last/" + path + " " + tempNameParent +
                        " --label now/" + path + " " + tempName;

  FILE *p = popen(command.c_str(), "r");
  std::string result{};
  char c = fgetc(p);
  while (c != EOF) {
    result.push_back(c);
    c = getc(p);
  }

  return result;
}
