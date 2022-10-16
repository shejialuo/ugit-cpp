/**
 * @file kSubcommand.hpp
 * @author shejialuo
 * @brief k subcommand
 *
 */

#ifndef _UIG_CPP_K_SUBCOMMAND_HPP_
#define _UIG_CPP_K_SUBCOMMAND_HPP_

#include "CLI/CLI.hpp"

namespace ugit {
void setKSubcommand(CLI::App &app);
void runKSubcommand();
}  // namespace ugit

#endif  // _UIG_CPP_K_SUBCOMMAND_HPP_
