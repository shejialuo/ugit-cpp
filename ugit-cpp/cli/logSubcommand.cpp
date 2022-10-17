/**
 * @file logSubcommand.cpp
 * @author shejialuo
 *
 */

#include "logSubcommand.hpp"

#include "base.hpp"
#include "data.hpp"

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
 *
 * @param opt
 */
void ugit::runLogSubcommand(const LogSubcommandOptions &opt) {
  std::string commitID = ugit::resolveObjectID(opt.commitID);
  while (!commitID.empty()) {
    auto commit = ugit::getCommit(commitID);
    std::cout << "commit " << commitID << "\n";
    std::cout << "\n" << commit.commitMessage << "\n\n";

    commitID = commit.parentCommitID;
  }
}
