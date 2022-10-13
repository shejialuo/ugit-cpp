/**
 * @file checkoutSubcommand.hpp
 * @author shejialuo
 * @brief checkout subcommand
 *
 */

#ifndef _UGIT_CPP_CLI_CHECKOUT_SUBCOMMAND_
#define _UGIT_CPP_CLI_CHECKOUT_SUBCOMMAND_

#include "CLI/CLI.hpp"

#include <string>

struct CheckoutSubcommandOptions {
  std::string commitID;
};

namespace ugit {
void setCheckoutSubcommand(CLI::App &app);
void runCheckoutSubcommand(CheckoutSubcommandOptions const &opt);
}  // namespace ugit

#endif
