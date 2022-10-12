/**
 * @file writeTreeSubcommand.hpp
 * @author shejialuo
 * @brief write-tree subcommand
 *
 */

#ifndef _UGIT_CPP_CLI_WRITE_TREE_SUBCOMMAND_HPP_
#define _UGIT_CPP_CLI_WRITE_TREE_SUBCOMMAND_HPP_

#include "CLI/CLI.hpp"

#include <string>

namespace ugit {
void setWriteTreeSubcommand(CLI::App &app);
void runWriteTreeSubcommand();
}  // namespace ugit

#endif  // _UGIT_CPP_CLI_WRITE_TREE_SUBCOMMAND_HPP_
