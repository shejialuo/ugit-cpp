include_directories(../data/)

add_library(cli STATIC cli.cpp initSubcommand.cpp hashObjectSubcommand.cpp
  catFileSubcommand.cpp writeTreeSubcommand.cpp readTreeSubcommand.cpp
  commitSubcommand.cpp logSubcommand.cpp checkoutSubcommand.cpp
  tagSubcommand.cpp kSubcommand.cpp branchSubcommand.cpp statusSubcommand.cpp
  resetSubcommand.cpp showSubcommand.cpp)
target_link_libraries(cli PRIVATE spdlog::spdlog CLI11::CLI11 data)
