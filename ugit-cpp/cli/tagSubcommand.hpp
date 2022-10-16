/**
 * @file tagSubcommand.hpp
 * @author shejialuo
 * @brief tab subcommand
 *
 */

#ifndef _UGIT_CPP_CLI_TAG_SUBCOMMAND_HPP_
#define _UGIT_CPP_CLI_TAG_SUBCOMMAND_HPP_

#include "CLI/CLI.hpp"

struct TagSubcommandOptions {
  std::string tagName;
  std::string objectID;
};

namespace ugit {
void setTagSubcommand(CLI::App &app);
void runTagSubcommand(TagSubcommandOptions const &opt);
}  // namespace ugit

#endif  // _UGIT_CPP_CLI_TAG_SUBCOMMAND_HPP_
