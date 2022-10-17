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
  tag->add_option("tag name", opt->tagName)->required();
  tag->add_option("object id", opt->objectID);
  tag->callback([opt]() { ugit::runTagSubcommand(*opt); });
}

/**
 * @brief call `ugit::createTag`
 *
 * @param opt
 */
void ugit::runTagSubcommand(TagSubcommandOptions const &opt) {
  std::string objectID = ugit::resolveObjectID(opt.objectID);
  if (objectID.empty()) {
    objectID = std::get<1>(ugit::getRef("HEAD"));
  }
  ugit::createTag(opt.tagName, objectID);
}
