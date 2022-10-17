/**
 * @file resetSubcommand.hpp
 * @author shejialuo
 * @brief reset subcommand
 *
 */

#ifndef _UGIT_CPP_CLI_RESET_SUBCOMMAND_HPP_
#define _UGIT_CPP_CLI_RESET_SUBCOMMAND_HPP_

#include "CLI/CLI.hpp"

#include <string>

struct ResetSubcommandOptions {
  std::string commitID;
};

namespace ugit {
void setResetSubcommand(CLI::App &app);
void runResetSubcommand(const ResetSubcommandOptions &opt);
}  // namespace ugit

#endif  // _UGIT_CPP_CLI_RESET_SUBCOMMAND_HPP_
