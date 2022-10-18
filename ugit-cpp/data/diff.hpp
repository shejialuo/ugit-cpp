/**
 * @file diff.hpp
 * @author shejialuo
 * @brief diff functionality
 *
 */

#ifndef _UGIT_CPP_DATA_DIFF_HPP_
#define _UGIT_CPP_DATA_DIFF_HPP_

#include <string>

namespace ugit {
std::string diffTrees(const std::string &tree1, const std::string &tree2);
}  // namespace ugit

#endif
