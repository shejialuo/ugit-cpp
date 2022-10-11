include_directories(../data/)

add_library(cli STATIC cli.cpp initSubcommand.cpp hashObjectSubcommand.cpp
  catFileSubcommand.cpp)
target_link_libraries(cli PRIVATE spdlog::spdlog CLI11::CLI11 data)
