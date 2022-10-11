add_library(data STATIC data.cpp)
target_link_libraries(data PRIVATE spdlog::spdlog)
