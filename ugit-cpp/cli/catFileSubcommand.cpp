/**
 * @file catFileSubcommand.cpp
 * @author shejialuo
 *
 */

#include "catFileSubcommand.hpp"

#include "base.hpp"
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

  catFile->add_option("blob id", opt->blobID, "blob object id")->required();
  catFile->callback([opt]() { runCatFileSubcommand(*opt); });
}

/**
 * @brief call `ugit::catFile`. cat-file can only display the content
 * of the blob object. If it is not the blob type, it will exit immediately.
 *
 * @param opt
 */
void ugit::runCatFileSubcommand(CatFileSubcommandOptions const &opt) {
  std::string blobID = ugit::resolveObjectID(opt.blobID);
  std::cout << ugit::getObject(blobID);
}
