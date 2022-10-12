/**
 * @file readTreeSubcommand.hpp
 * @author shejialuo
 * @brief read-tree subcommand
 *
 */

#ifndef _UGIT_CPP_CLI_READ_TREE_SUBCOMMAND_HPP_
#define _UGIT_CPP_CLI_READ_TREE_SUBCOMMAND_HPP_

#include "CLI/CLI.hpp"

#include <string>

// Here, we use struct although there may be only one
// field. We need extensible way
struct ReadTreeSubcommandOptions {
  std::string object;
};

namespace ugit {
void setReadTreeSubcommand(CLI::App &app);
void runReadTreeSubcommand(ReadTreeSubcommandOptions const &opt);
}  // namespace ugit

#endif  // _UGIT_CPP_CLI_READ_TREE_SUBCOMMAND_HPP_