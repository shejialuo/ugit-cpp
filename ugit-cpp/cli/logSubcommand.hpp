/**
 * @file logSubcommand.hpp
 * @author shejialuo
 * @brief log subcommand
 *
 */

#ifndef _UGIT_CPP_CLI_LOG_SUBCOMMAND_HPP_
#define _UGIT_CPP_CLI_LOG_SUBCOMMAND_HPP_

#include "CLI/CLI.hpp"

#include <string>

struct LogSubcommandOptions {
  std::string commitID;
};

namespace ugit {
void setLogSubcommand(CLI::App &app);
void runLogSubcommand(const LogSubcommandOptions &opt);
}  // namespace ugit

#endif  // _UGIT_CPP_CLI_LOG_SUBCOMMAND_HPP_