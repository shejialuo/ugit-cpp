/**
 * @file resetSubcommand.cpp
 * @author shejialuo
 *
 */

#include "resetSubcommand.hpp"

#include "base.hpp"

#include <memory>

void ugit::setResetSubcommand(CLI::App &app) {
  auto opt = std::make_shared<ResetSubcommandOptions>();
  auto *reset = app.add_subcommand("reset", "move HEAD to a commit object id");

  reset->add_option("commit id", opt->commitID, "commit object id");
  reset->callback([opt]() { ugit::runResetSubcommand(*opt); });
}

void ugit::runResetSubcommand(const ResetSubcommandOptions &opt) { ugit::reset(opt.commitID); }
