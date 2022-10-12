/**
 * @file writeTreeSubcommand.cpp
 * @author shejialuo
 */

#include "writeTreeSubcommand.hpp"

#include "CLI/CLI.hpp"
#include "base.hpp"

#include <iostream>

/**
 * @brief Set up the write-tree command
 *
 * @param app CLI::App
 */
void ugit::setWriteTreeSubcommand(CLI::App &app) {
  auto *writeTree = app.add_subcommand("write-tree", "create a tree object from the current index");
  writeTree->callback([]() { ugit::runWriteTreeSubcommand(); });
}

/**
 * @brief call `ugit::writeTree()`
 *
 */
void ugit::runWriteTreeSubcommand() {
  std::string treeID = ugit::writeTree();
  std::cout << treeID << "\n";
}
