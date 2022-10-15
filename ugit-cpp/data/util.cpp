/**
 * @file util.cpp
 * @author shejialuo
 */

#include "util.hpp"

#include "err.hpp"
#include "spdlog/spdlog.h"

#include <filesystem>
#include <fstream>
#include <iterator>
#include <openssl/sha.h>

std::string bytesToHexString(const std::vector<uint8_t> &input);

/**
 * @brief generate shA1sum hex string
 *
 * @param data the binary data of the file.
 * @return std::string hex data string
 */
std::string ugit::sha1sumHex(const std::vector<uint8_t> &data) {
  std::vector<uint8_t> sha1SumValue{};
  sha1SumValue.resize(SHA_DIGEST_LENGTH);

  SHA1(reinterpret_cast<const unsigned char *>(&data[0]),
       data.size(),
       reinterpret_cast<unsigned char *>(&sha1SumValue[0]));
  return bytesToHexString(sha1SumValue);
}

/**
 * @brief Use table to get hex string value
 *
 * @param data the sha1sum binary data
 * @return std::string std::string hex data string
 */
std::string bytesToHexString(const std::vector<uint8_t> &data) {
  static const char characters[] = "0123456789abcdef";

  std::string ret(data.size() * 2, 0);

  auto buf = const_cast<char *>(ret.data());

  // Here, we use Lookup table method
  for (const auto &oneInputByte : data) {
    // Get the highest 4 bit
    *buf++ = characters[oneInputByte >> 4];
    // Get the lowest 4 bit
    *buf++ = characters[oneInputByte & 0x0F];
  }
  return ret;
}

/**
 * @brief Parse the `content` and returns the types and also
 * removes the type from content
 *
 * @param type the type user should passed, which should be empty.
 * @param content the object file content
 */
void ugit::getTypeAndRemoveType(std::string &type, std::string &content) {
  size_t i = 0;
  for (char c : content) {
    if (c == ' ')
      break;
    type.push_back(c);
    i++;
  }
  content.erase(0, i + 1);
}

/**
 * @brief Read the file and write the binary data into data.
 *
 * @param filepath file path
 * @return std::vector<uint8_t> return the binary data
 */
std::vector<uint8_t> ugit::readBinaryFromFile(const std::string &filepath) {
  using namespace std::filesystem;
  path file{filepath};
  if (!exists(file)) {
    spdlog::error("{} does not exist", filepath);
    exit(static_cast<int>(ugit::Error::FileNotExist));
  }
  std::ifstream fs{file, std::ios::binary};
  std::vector<uint8_t> data{std::istreambuf_iterator<char>(fs), {}};
  fs.close();
  return data;
}

/**
 * @brief
 *
 * @param filepath
 * @return std::string
 */
std::string ugit::readStringFromFile(const std::string &filepath) {
  using namespace std::filesystem;
  path file{filepath};
  if (!exists(file)) {
    spdlog::error("{} does not exist", filepath);
    exit(static_cast<int>(ugit::Error::FileNotExist));
  }
  std::ifstream fs{file, std::ios::binary};
  std::string data{std::istreambuf_iterator<char>(fs), {}};
  fs.close();
  return data;
}

/**
 * @brief Write `str` to filepath
 *
 * @param filepath the file
 * @param str the pointer
 * @param size the size of the string
 * @return bool true means successful
 */
bool ugit::writeBinaryToFile(const std::string &filepath, const char *str, int size) {
  std::ofstream os{filepath, std::ios::trunc | std::ios::binary};
  if (!os.is_open()) {
    return false;
  }
  os.write(str, size);
  os.close();
  return true;
}
