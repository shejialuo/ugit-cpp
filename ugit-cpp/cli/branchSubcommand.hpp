/**
 * @file branchSubcommand.hpp
 * @author shejialuo
 * @brief branch subcommand
 *
 */

#ifndef _UGIT_CPP_CLI_BRANCH_SUBCOMMAND_
#define _UGIT_CPP_CLI_BRANCH_SUBCOMMAND_

#include "CLI/CLI.hpp"

struct BranchSubcommandOptions {
  std::string branchName;
  std::string commitID;
};

namespace ugit {
void setBranchSubcommand(CLI::App &app);
void runBranchSubcommand(BranchSubcommandOptions const &opt);
}  // namespace ugit

#endif  // _UGIT_CPP_CLI_BRANCH_SUBCOMMAND_
