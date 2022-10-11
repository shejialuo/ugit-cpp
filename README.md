# ugit-cpp

This is the implementation of [ugit](https://www.leshenko.net/p/ugit/#) by myself.

## Development Setup

For setting up the development environment. You must develop in the UNIX-like environment
with the following requirements:

+ Latest `gcc` or `clang` for compilation.
+ Latest `cmake` for building the project.
+ `clang-format` for formatting the code.
+ Doxygen and graphviz for building the docs

## External Libraries

There are some external libraries we use in this project. And we manage it with `git submodule`.

+ [spdlog](https://github.com/gabime/spdlog) used for logging.
+ [CLI11](https://github.com/CLIUtils/CLI11) used for command line parser
