/**
 * @file catFileSubcommand.cpp
 * @author shejialuo
 *
 */

#include "catFileSubcommand.hpp"

#include "data.hpp"

#include <iostream>
#include <memory>

/**
 * @brief Set up the cat-file command
 *
 * @param app CLI::App
 */
void ugit::setCatFileSubcommand(CLI::App &app) {
  auto opt = std::make_shared<CatFileSubcommandOptions>();
  auto *catFile = app.add_subcommand("cat-file", "provide content for repository objects");

  catFile->add_option("strings", opt->object, "object id")->required();
  catFile->callback([opt]() { runCatFileSubcommand(*opt); });
}

/**
 * @brief call ugit::catFile(opt.object)
 *
 * @param opt
 */
void ugit::runCatFileSubcommand(CatFileSubcommandOptions const &opt) { std::cout << ugit::getObject(opt.object); }
