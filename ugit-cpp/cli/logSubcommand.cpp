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
  log->add_option("strings", opt->commitID, "commit id");
  log->callback([opt]() { runLogSubcommand(*opt); });
}

/**
 * @brief call `ugit::getCommit` to get the commit message.
 * and get the parent object ID. And recursively do this.
 *
 * @param opt
 */
void ugit::runLogSubcommand(const LogSubcommandOptions &opt) {
  std::string objectID = opt.commitID;
  if (objectID.empty()) {
    objectID = ugit::getHead();
  }
  while (!objectID.empty()) {
    auto commit = ugit::getCommit(objectID);
    std::cout << "commit " << objectID << "\n";
    std::cout << "\n" << std::get<2>(commit) << "\n\n";

    objectID = std::get<1>(commit);
  }
}
