/**
 * @file initSubcommand.cpp
 * @author shejialuo
 *
 */

#include "initSubcommand.hpp"

#include "data.hpp"

#include <iostream>

/**
 * @brief Setup the Init Subcommand
 *
 * @param app CLI::App
 */
void ugit::setInitSubcommand(CLI::App &app) {
  auto *init = app.add_subcommand("init", "initialize the ugit repository");
  init->callback([]() { ugit::runInitSubcommand(); });
}

/**
 * @brief Run the Init SubCommand
 *
 */
void ugit::runInitSubcommand() { ugit::initialization(); }
