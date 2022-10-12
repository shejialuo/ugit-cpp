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
std::string sha1sumHex(const std::vector<uint8_t> &data);
void getTypeAndRemoveType(std::string &type, std::string &content);
std::vector<uint8_t> readBinaryFromFile(const std::string &filepath);
}  // namespace ugit

#endif  // _UGIT_CPP_DATA_UTIL_HPP_
