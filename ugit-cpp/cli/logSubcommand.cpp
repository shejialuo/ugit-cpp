/**
 * @file logSubcommand.cpp
 * @author shejialuo
 *
 */

#include "logSubcommand.hpp"

#include "base.hpp"
#include "data.hpp"
#include "util.hpp"

#include <algorithm>
#include <iterator>
#include <memory>
#include <utility>

/**
 * @brief set log subcommand
 *
 * @param app CLI::App
 */
void ugit::setLogSubcommand(CLI::App &app) {
  auto opt = std::make_shared<LogSubcommandOptions>();
  auto *log = app.add_subcommand("log", "show commit logs");
  log->add_option("commit id", opt->commitID, "commit object id");
  log->callback([opt]() { runLogSubcommand(*opt); });
}

/**
 * @brief call `ugit::getCommit` to get the commit message.
 * and get the parent object ID. And recursively do this.
 * Also show references that point to each point.
 *
 * @param opt
 */
void ugit::runLogSubcommand(const LogSubcommandOptions &opt) {
  std::string commitID = ugit::resolveObjectID(opt.commitID);

  std::unordered_map<std::string, ugit::RefContainer> refMap{};
  std::unordered_map<std::string, std::vector<std::string>> commitToReferences{};
  ugit::iterateRefs(refMap);
  // We need to get the mapping from commit object id to reference
  for (auto &ref : refMap) {
    commitToReferences[ref.second.value].push_back(ref.first);
  }

  while (!commitID.empty()) {
    auto commit = ugit::getCommit(commitID);
    ugit::printCommitMessage(commitID, commitToReferences, commit.commitMessage);
    commitID = commit.parentCommitID;
  }
}
