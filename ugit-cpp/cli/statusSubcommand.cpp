/**
 * @file statusSubcommand.cpp
 * @author shejialuo
 *
 */

#include "statusSubcommand.hpp"

#include "base.hpp"

#include <iostream>

void ugit::setStatusSubcommand(CLI::App &app) {
  auto *status = app.add_subcommand("status", "print information");
  status->callback([]() { ugit::runStatusSubcommand(); });
}

void ugit::runStatusSubcommand() {
  std::string objectID = ugit::resolveObjectID("HEAD");
  std::string branchName = ugit::getBranchName();
  if (!branchName.empty()) {
    std::cout << "On branch " << branchName << "\n";
  } else {
    std::cout << "HEAD detached at " << objectID << "\n";
  }
}
