/**
 * @file hashObjectSubcommand.cpp
 * @author shejialuo
 *
 */

#include "hashObjectSubcommand.hpp"

#include "data.hpp"
#include "err.hpp"
#include "spdlog/spdlog.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
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
 * @brief open the `opt.file` and call `ugit::hasObject()` for later processing
 *
 * @param opt hashObjectSubcommand arguments
 */
void ugit::runHashObjectSubcommand(HashObjectSubcommandOptions const &opt) {
  using namespace std::filesystem;
  path file{opt.file};
  if (!exists(file)) {
    spdlog::error("{} does not exist", opt.file);
    exit(static_cast<int>(ugit::Error::FileNotExist));
  }
  std::ifstream fs{file, std::ios::binary};
  const std::vector<uint8_t> data{std::istreambuf_iterator<char>(fs), {}};
  fs.close();
  std::string objectID = ugit::hashObject(data);
  std::cout << objectID << "\n";
}
