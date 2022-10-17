/**
 * @file checkoutSubcommand.cpp
 * @author shejialuo
 *
 */

#include "checkoutSubcommand.hpp"

#include "base.hpp"

#include <memory.h>

/**
 * @brief Set up the checkout subcommand
 *
 * @param app
 */
void ugit::setCheckoutSubcommand(CLI::App &app) {
  auto opt = std::make_shared<CheckoutSubcommandOptions>();
  auto *checkout = app.add_subcommand("checkout", "switch branches or restore working tree files");

  checkout->add_option("commit id", opt->commitID, "commit object id")->required();
  checkout->callback([opt]() { ugit::runCheckoutSubcommand(*opt); });
}

/**
 * @brief  call `ugit::checkout`
 *
 * @param opt
 */
void ugit::runCheckoutSubcommand(const CheckoutSubcommandOptions &opt) { ugit::checkout(opt.commitID); }
