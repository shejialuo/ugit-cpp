/**
 * @file diffSubcommand.cpp
 * @author shejialuo
 *
 */

#include "diffSubcommand.hpp"

#include "base.hpp"
#include "data.hpp"
#include "diff.hpp"

#include <memory>

void ugit::setDiffSubcommand(CLI::App &app) {
  auto opt = std::make_shared<DiffSubcommandOptions>();
  auto *diff = app.add_subcommand("diff", "show changes");
  diff->add_option("commit", opt->name, "commit object id or symbolic name");
  diff->callback([opt]() { runDiffSubcommand(*opt); });
}

void ugit::runDiffSubcommand(const DiffSubcommandOptions &opt) {
  std::string commitID = ugit::resolveObjectID(opt.name);
  auto commit = ugit::getCommit(commitID);

  std::cout << ugit::diffTrees(ugit::getWorkspaceTree(), ugit::getObject(commit.treeID, "tree"));
}
