/**
 * @file data.cpp
 * @author shejialuo
 *
 */

#include "data.hpp"

#include "err.hpp"
#include "spdlog/spdlog.h"

#include <filesystem>
#include <string_view>

constexpr std::string_view GIT_DIR = ".ugit";

void ugit::initialization() {
  using namespace std::filesystem;
  if (!create_directory(GIT_DIR)) {
    spdlog::error("create directory {} failed", GIT_DIR);
    exit(static_cast<int>(ugit::Error::CraeteFileError));
  }
  spdlog::info("create directorty {}", GIT_DIR);
}
