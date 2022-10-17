/**
 * @file util.hpp
 * @author shejialuo
 * @brief some util for data operations
 *
 */

#ifndef _UGIT_CPP_DATA_UTIL_HPP_
#define _UGIT_CPP_DATA_UTIL_HPP_

#include <string>
#include <vector>

namespace ugit {

struct CommitMessage {
  std::string treeID{};
  std::string parentCommitID{};
  std::string commitMessage{};
  CommitMessage() {}
  CommitMessage(std::string &t, std::string &p, std::string &m) : treeID{t}, parentCommitID{p}, commitMessage{m} {}
};

struct RefContainer {
  bool symbolic = false;
  std::string value{};
  RefContainer() {}
  RefContainer(bool s, std::string v) : symbolic{s}, value{v} {}
};

std::string sha1sumHex(const std::vector<uint8_t> &data);
void getTypeAndRemoveType(std::string &type, std::string &content);
std::vector<uint8_t> readBinaryFromFile(const std::string &filepath);
std::string readStringFromFile(const std::string &filepath);
bool writeBinaryToFile(const std::string &filepath, const char *str, int size);
}  // namespace ugit

#endif  // _UGIT_CPP_DATA_UTIL_HPP_
