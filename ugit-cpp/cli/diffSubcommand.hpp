/**
 * @file diffSubcommand.hpp
 * @author shejialuo
 * @brief diff subcommand
 *
 */

#ifndef _UGIT_CPP_CLI_DIFF_SUBCOMMAND_
#define _UGIT_CPP_CLI_DIFF_SUBCOMMAND_

#include "CLI/CLI.hpp"

struct DiffSubcommandOptions {
  std::string name;
};

namespace ugit {
void setDiffSubcommand(CLI::App &app);
void runDiffSubcommand(const DiffSubcommandOptions &opt);
}  // namespace ugit

#endif
