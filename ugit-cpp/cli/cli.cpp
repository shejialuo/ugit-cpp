/**
 * @file cli.cpp
 * @author shejialuo
 */

#include "cli.hpp"

#include "branchSubcommand.hpp"
#include "catFileSubcommand.hpp"
#include "checkoutSubcommand.hpp"
#include "commitSubcommand.hpp"
#include "hashObjectSubcommand.hpp"
#include "initSubcommand.hpp"
#include "kSubcommand.hpp"
#include "logSubcommand.hpp"
#include "readTreeSubcommand.hpp"
#include "resetSubcommand.hpp"
#include "showSubcommand.hpp"
#include "statusSubcommand.hpp"
#include "tagSubcommand.hpp"
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
  ugit::setCheckoutSubcommand(app);
  ugit::setTagSubcommand(app);
  ugit::setKSubcommand(app);
  ugit::setBranchSubcommand(app);
  ugit::setStatusSubcommand(app);
  ugit::setResetSubcommand(app);
  ugit::setShowSubcommand(app);
}
