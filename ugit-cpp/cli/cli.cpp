/**
 * @file cli.cpp
 * @author shejialuo
 */

#include "cli.hpp"

#include "catFileSubcommand.hpp"
#include "commitSubcommand.hpp"
#include "hashObjectSubcommand.hpp"
#include "initSubcommand.hpp"
#include "logSubcommand.hpp"
#include "readTreeSubcommand.hpp"
#include "writeTreeSubcommand.hpp"

/**
 * @brief Add flags, options and subcommands
 *
 * `init` subcommand: initialize the ugit-cpp repository
 *
 * @param app CLI::App
 */
void ugit::parseArgs(CLI::App &app) {
  ugit::setInitSubcommand(app);
  ugit::setHashObjectSubcommand(app);
  ugit::setCatFileSubcommand(app);
  ugit::setWriteTreeSubcommand(app);
  ugit::setReadTreeSubcommand(app);
  ugit::setCommitSubcommand(app);
  ugit::setLogSubcommand(app);
}
