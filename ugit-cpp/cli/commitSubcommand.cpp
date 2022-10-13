/**
 * @file commitSubcommand.cpp
 * @author shejialuo
 *
 */

#include "commitSubcommand.hpp"

#include "base.hpp"

#include <iostream>
#include <memory>

/**
 * @brief Set up the commit subcommand
 *
 * @param app CLI::App
 */
void ugit::setCommitSubcommand(CLI::App &app) {
  auto opt = std::make_shared<CommitSubcommandOptions>();
  auto *commit = app.add_subcommand("commit", "record changes to the repository");

  commit->add_option("-m, --message", opt->message, "record message")->required();
  commit->callback([opt]() { ugit::runCommitSubcommand(*opt); });
}

/**
 * @brief call `ugit::commit`
 *
 * @param opt
 */
void ugit::runCommitSubcommand(CommitSubcommandOptions const &opt) {
  std::string commitID = ugit::commit(opt.message);
  std::cout << commitID << "\n";
}
