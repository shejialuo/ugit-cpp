/**
 * @file branchSubcommand.cpp
 * @author shejialuo
 *
 */

#include "branchSubcommand.hpp"

#include "base.hpp"
#include "data.hpp"
#include "spdlog/spdlog.h"

#include <memory>

/**
 * @brief Set up branch subcommand
 *
 * @param app
 */
void ugit::setBranchSubcommand(CLI::App &app) {
  auto opt = std::make_shared<BranchSubcommandOptions>();
  auto *branch = app.add_subcommand("branch", "create new branch");

  branch->add_option("branch name", opt->branchName, "the branch name")->required();
  branch->add_option("commit ID", opt->commitID, "commit object id");
  branch->callback([opt]() { ugit::runBranchSubcommand(*opt); });
}

void ugit::runBranchSubcommand(BranchSubcommandOptions const &opt) {
  std::string commitID = ugit::resolveObjectID(opt.commitID);
  ugit::createBranch(opt.branchName, commitID);
  spdlog::info("Branch {} created at {}", opt.branchName, commitID);
}
