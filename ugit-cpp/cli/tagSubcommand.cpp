/**
 * @file tagSubcommand.cpp
 * @author shejialuo
 *
 */

#include "tagSubcommand.hpp"

#include "base.hpp"
#include "data.hpp"

#include <iostream>
#include <memory>

/**
 * @brief Set up the tag subcommand
 *
 * @param app
 */
void ugit::setTagSubcommand(CLI::App &app) {
  auto opt = std::make_shared<TagSubcommandOptions>();
  auto *tag = app.add_subcommand("tag", "create a name for objectID");
  tag->add_option("strings", opt->tagName)->required();
  tag->add_option("strings", opt->commitID);
  tag->callback([opt]() { ugit::runTagSubcommand(*opt); });
}

/**
 * @brief call `ugit::createTag`
 *
 * @param opt
 */
void ugit::runTagSubcommand(TagSubcommandOptions const &opt) {
  std::string commitID = opt.commitID;
  if (commitID.empty()) {
    commitID = ugit::getRef("HEAD");
  }
  ugit::createTag(opt.tagName, commitID);
}
