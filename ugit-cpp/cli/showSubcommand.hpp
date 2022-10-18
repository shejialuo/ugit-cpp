/**
 * @file showSubcommand.hpp
 * @author shejialuo
 * @brief show subcommand
 *
 */

#ifndef _UGIT_CPP_CLI_SHOW_SUBCOMMAND_HPP_
#define _UGIT_CPP_CLI_SHOW_SUBCOMMAND_HPP_

#include "CLI/App.hpp"

#include <string>

struct ShowSubcommandOption {
  std::string name;
};

namespace ugit {
void setShowSubcommand(CLI::App &app);
void runShowSubcommand(ShowSubcommandOption const &opt);
}  // namespace ugit

#endif  // _UGIT_CPP_CLI_SHOW_SUBCOMMAND_HPP_
