/**
 * @file commitSubcommand.hpp
 * @author shejialuo
 * @brief commit subcommand
 *
 */

#ifndef _UGIT_CPP_CLI_COMMIT_SUBCOMMAND_HPP_
#define _UGIT_CPP_CLI_COMMIT_SUBCOMMAND_HPP_

#include "CLI/CLI.hpp"

struct CommitSubcommandOptions {
  std::string message;
};

namespace ugit {
void setCommitSubcommand(CLI::App &app);
void runCommitSubcommand(CommitSubcommandOptions const &opt);
}  // namespace ugit

#endif  // _UGIT_CPP_CLI_COMMIT_SUBCOMMAND_HPP_
