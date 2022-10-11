/**
 * @file hashObjectSubcommand.hpp
 * @author shejialuo
 * @brief hashObjectCommand
 *
 */

#ifndef _UGIT_CPP_CLI_HASH_OBJECT_SUBCOMMAND_HPP_
#define _UGIT_CPP_CLI_HASH_OBJECT_SUBCOMMAND_HPP_

#include "CLI/CLI.hpp"

#include <string>

// Here, we use struct although there may be only one
// field. We need extensible way
struct HashObjectSubcommandOptions {
  std::string file;
};

namespace ugit {
void setHashObjectSubcommand(CLI::App &app);
void runHashObjectSubcommand(HashObjectSubcommandOptions const &opt);
}  // namespace ugit

#endif  // _UGIT_CPP_CLI_HASH_OBJECT_SUBCOMMAND_HPP_
