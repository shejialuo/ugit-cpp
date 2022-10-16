/**
 * @file data.hpp
 * @author shejialuo
 * @brief operation for `.ugit` directory
 *
 */

#ifndef _UGIT_CPP_DATA_DATA_HPP_
#define _UGIT_CPP_DATA_DATA_HPP_

#include <string>
#include <unordered_map>
#include <vector>

namespace ugit {
void initialization();
std::string hashObject(const std::vector<uint8_t> &data, std::string type = "blob");
std::string getObject(std::string object, std::string type = "blob");
void updateRef(std::string ref, std::string objectID);
std::string getRef(std::string ref);
void iterateRefs(std::unordered_map<std::string, std::string> &refMap);
}  // namespace ugit

#endif  // _UGIT_CPP_DATA_DATA_HPP_
