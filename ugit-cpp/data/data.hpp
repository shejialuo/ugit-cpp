/**
 * @file data.hpp
 * @author shejialuo
 * @brief operation for `.ugit` directory
 *
 */

#ifndef _UGIT_CPP_DATA_DATA_HPP_
#define _UGIT_CPP_DATA_DATA_HPP_

#include "util.hpp"

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace ugit {
void initializationDirectories();
std::string hashObject(const std::vector<uint8_t> &data, std::string type = "blob");
std::string getObject(std::string objectID, std::string type = "blob");
void updateRef(std::string ref, ugit::RefContainer value, bool deref = true);
ugit::RefContainer getRef(std::string ref, bool deref = true);
void iterateRefs(std::unordered_map<std::string, ugit::RefContainer> &refMap, bool deref);
}  // namespace ugit

#endif  // _UGIT_CPP_DATA_DATA_HPP_
