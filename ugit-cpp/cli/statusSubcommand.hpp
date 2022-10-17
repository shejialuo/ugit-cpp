/**
 * @file statusSubcommand.hpp
 * @author shejialuo
 * @brief status subcommand
 *
 */

#ifndef _UGIT_CPP_CLI_STATUS_SUBCOMMAND_HPP_
#define _UGIT_CPP_CLI_STATUS_SUBCOMMAND_HPP_

#include "CLI/CLI.hpp"

namespace ugit {
void setStatusSubcommand(CLI::App &app);
void runStatusSubcommand();
}  // namespace ugit

#endif  // _UGIT_CPP_CLI_STATUS_SUBCOMMAND_HPP_
