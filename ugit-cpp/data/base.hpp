/**
 * @file base.hpp
 * @author shejialuo
 * @brief upper level operation
 *
 */

#ifndef _UGIT_CPP_DATA_BASE_HPP_
#define _UGIT_CPP_DATA_BASE_HPP_

#include "util.hpp"

#include <string>
#include <utility>
#include <vector>

namespace ugit {
void initialization();
std::string writeTree(std::string directory = ".");
void readTree(std::string treeID);
std::string commit(std::string message);
ugit::CommitMessage getCommit(std::string commitID);
void checkout(std::string name);
void createTag(std::string tagName, std::string objectID);
std::string resolveObjectID(std::string name);
void createBranch(std::string branchName, std::string commitID);
std::string getBranchName();
std::vector<std::string> getBranchNames();
void reset(std::string commitID);
std::string getWorkspaceTree();
}  // namespace ugit

#endif  // _UGIT_CPP_DATA_BASE_HPP_
