/**
 * @file data.hpp
 * @author shejialuo
 * @brief operation for `.ugit` directory
 *
 */

#ifndef _UGIT_CPP_DATA_DATA_HPP_
#define _UGIT_CPP_DATA_DATA_HPP_

#include <string>

namespace ugit {
void initialization();
std::string hashObject(std::string file);
}  // namespace ugit

#endif  // _UGIT_CPP_DATA_DATA_HPP_
