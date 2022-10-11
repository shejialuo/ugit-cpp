/**
 * @file initSubcommand.hpp
 * @author shejialuo
 * @brief init subcommand
 *
 */

#ifndef _UGIT_CPP_CLI_INIT_SUBCOMMAND_HPP
#define _UGIT_CPP_CLI_INIT_SUBCOMMAND_HPP

#include "CLI/CLI.hpp"

namespace ugit {
void setInitSubcommand(CLI::App &app);
void runInitSubcommand();
}  // namespace ugit

#endif  // _UGIT_CPP_CLI_INIT_SUBCOMMAND_HPP
