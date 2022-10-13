/**
 * @file base.hpp
 * @author shejialuo
 * @brief upper level operation
 *
 */

#ifndef _UGIT_CPP_DATA_BASE_HPP_
#define _UGIT_CPP_DATA_BASE_HPP_

#include <string>

namespace ugit {
std::string writeTree(std::string directory = ".");
void readTree(std::string treeID);
std::string commit(std::string message);
}  // namespace ugit

#endif  // _UGIT_CPP_DATA_BASE_HPP_
