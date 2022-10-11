/**
 * @file hashObjectSubcommand.cpp
 * @author shejialuo
 *
 */

#include "hashObjectSubcommand.hpp"

#include "data.hpp"

#include <iostream>
#include <memory>
#include <string>

/**
 * @brief Setup the hash-object Subcommand
 *
 * @param app CLI::App
 */
void ugit::setHashObjectSubcommand(CLI::App &app) {
  auto opt = std::make_shared<HashObjectSubcommandOptions>();
  auto *hashObject = app.add_subcommand("hash-object", "compute object ID and creates a blob");
  hashObject->add_option("files", opt->file, "file name")->required();

  hashObject->callback([opt]() { runHashObjectSubcommand(*opt); });
}

/**
 * @brief call ugit::hashObject(opt.file)
 *
 * @param opt hashObjectSubcommand arguments
 */
void ugit::runHashObjectSubcommand(HashObjectSubcommandOptions const &opt) {
  std::string objectID = ugit::hashObject(opt.file);
  std::cout << objectID << "\n";
}
