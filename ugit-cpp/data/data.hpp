/**
 * @file data.hpp
 * @author shejialuo
 * @brief operation for `.ugit` directory
 *
 */

#ifndef _UGIT_CPP_DATA_DATA_HPP_
#define _UGIT_CPP_DATA_DATA_HPP_

#include <string>
#include <vector>

namespace ugit {
void initialization();
std::string hashObject(const std::vector<uint8_t> &data, std::string type = "blob");
std::string getObject(std::string object, std::string type = "blob");
void setHead(std::string commitID);
std::string getHead();
}  // namespace ugit

#endif  // _UGIT_CPP_DATA_DATA_HPP_
