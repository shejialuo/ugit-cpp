/**
 * @file readTreeSubcommand.cpp
 * @author shejialuo
 */

#include "readTreeSubcommand.hpp"

#include "base.hpp"

#include <memory>

/**
 * @brief Setup the read-tree subcommand
 *
 * @param app CLI:App
 */
void ugit::setReadTreeSubcommand(CLI::App &app) {
  auto opt = std::make_shared<ReadTreeSubcommandOptions>();
  auto *readTree = app.add_subcommand("read-tree", "reads tree information into the index");

  readTree->add_option("strings", opt->object, "tree id")->required();
  readTree->callback([opt]() { ugit::runReadTreeSubcommand(*opt); });
}

/**
 * @brief call ugit::readTree
 *
 * @param opt
 */
void ugit::runReadTreeSubcommand(ReadTreeSubcommandOptions const &opt) { ugit::readTree(opt.object); }
