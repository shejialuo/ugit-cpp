# We need to link OpenSSL library for SHA1
find_package(OpenSSL REQUIRED)

add_library(data STATIC util.cpp data.cpp)
target_link_libraries(data PRIVATE spdlog::spdlog OpenSSL::Crypto)

add_subdirectory(./tests)
