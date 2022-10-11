/**
 * @file catFileSubcommand.hpp
 * @author shejialuo
 * @brief cat-file command
 *
 */

#ifndef _UGIT_CPP_CLI_CAT_FILE_SUBCOMMAND_HPP_
#define _UGIT_CPP_CLI_CAT_FILE_SUBCOMMAND_HPP_

#include "CLI/CLI.hpp"

#include <string>

// Here, we use struct although there may be only one
// field. We need extensible way
struct CatFileSubcommandOptions {
  std::string object;
};

namespace ugit {
void setCatFileSubcommand(CLI::App &app);
void runCatFileSubcommand(CatFileSubcommandOptions const &opt);
}  // namespace ugit

#endif  // _UGIT_CPP_CLI_CAT_FILE_SUBCOMMAND_HPP_
