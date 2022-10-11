add_library(cli STATIC cli.cpp initSubcommand.cpp)
target_link_libraries(cli PRIVATE spdlog::spdlog CLI11::CLI11)
