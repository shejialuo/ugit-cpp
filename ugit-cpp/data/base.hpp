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
std::string writeTree(std::string directory = ".");
void readTree(std::string treeID);
std::string commit(std::string message);
std::tuple<std::string, std::string, std::string> getCommit(std::string commitID);
void checkout(std::string commitID);
}  // namespace ugit

#endif  // _UGIT_CPP_DATA_BASE_HPP_
