/**
 * @file showSubcommand.cpp
 * @author shejialuo
 *
 */

#include "showSubcommand.hpp"

#include "base.hpp"
#include "data.hpp"
#include "diff.hpp"
#include "spdlog/spdlog.h"
#include "util.hpp"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

void ugit::setShowSubcommand(CLI::App &app) {
  auto opt = std::make_shared<ShowSubcommandOption>();
  auto *show = app.add_subcommand("show", "print commit message");

  show->add_option("commit", opt->name, "commit object id or symbolic name");
  show->callback([opt]() { ugit::runShowSubcommand(*opt); });
}

void ugit::runShowSubcommand(const ShowSubcommandOption &opt) {
  std::string commitID = ugit::resolveObjectID(opt.name);
  auto commit = ugit::getCommit(commitID);
  std::unordered_map<std::string, std::vector<std::string>> commitToReferences{};
  ugit::printCommitMessage(commitID, commitToReferences, commit.commitMessage);

  if (!commit.parentCommitID.empty()) {
    std::string parentTreeID = ugit::getCommit(commit.parentCommitID).treeID;
    std::cout << ugit::diffTrees(ugit::getObject(commit.treeID, "tree"), ugit::getObject(parentTreeID, "tree")) << "\n";
  }
}
