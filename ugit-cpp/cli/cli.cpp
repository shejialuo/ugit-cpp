/**
 * @file cli.cpp
 * @author shejialuo
 */

#include "cli.hpp"

#include "catFileSubcommand.hpp"
#include "hashObjectSubcommand.hpp"
#include "initSubcommand.hpp"

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
}
