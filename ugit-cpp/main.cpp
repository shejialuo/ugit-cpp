#include "CLI/CLI.hpp"
#include "cli/cli.hpp"

int main(int argc, char *argv[]) {
  CLI::App app{"ugit a git implementation by cpp "};
  ugit::parseArgs(app);
  CLI11_PARSE(app, argc, argv);
  return 0;
}