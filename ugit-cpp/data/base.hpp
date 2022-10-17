/**
 * @file base.hpp
 * @author shejialuo
 * @brief upper level operation
 *
 */

#ifndef _UGIT_CPP_DATA_BASE_HPP_
#define _UGIT_CPP_DATA_BASE_HPP_

#include <string>
#include <utility>

namespace ugit {
void initialization();
std::string writeTree(std::string directory = ".");
void readTree(std::string treeID);
std::string commit(std::string message);
std::tuple<std::string, std::string, std::string> getCommit(std::string commitID);
void checkout(std::string name);
void createTag(std::string tagName, std::string objectID);
std::string resolveObjectID(std::string name);
void createBranch(std::string branchName, std::string commitID);
}  // namespace ugit

#endif  // _UGIT_CPP_DATA_BASE_HPP_
