#include "util.hpp"

#include <cstdio>
#include <ctime>
#include <fstream>
#include <gtest/gtest.h>
#include <random>
#include <sys/stat.h>
#include <vector>

// Use `sha1sum` gnu coreutils to test the correctness
// of the `sha1sum`
TEST(UtilTest, Sha1Sum) {
  for (int i = 0; i < 1000; ++i) {
    std::string path = "/tmp/utilTestsha1sum";

    std::vector<uint8_t> sample{};
    std::string pathForTest = path;
    std::ofstream of{pathForTest, std::ios::trunc};
    if (!of.is_open()) {
      return;
    }
    srand(i);
    for (int j = 0; j < 1000; ++j) {
      sample.push_back(std::rand() % 255);
    }
    of.write(reinterpret_cast<char *>(&sample[0]), sample.size());
    of.close();
    std::string actual = ugit::sha1sumHex(sample);
    std::string command = "sha1sum " + pathForTest;
    FILE *file = popen(command.c_str(), "r");
    std::string should{};
    char c = fgetc(file);
    while (c != EOF && c != ' ') {
      should.push_back(c);
      c = getc(file);
    }
    EXPECT_EQ(actual, should);
  }
}

TEST(UtilTest, getTypeAndRemoveType) {
  std::string type{};
  std::string content{"12234 22"};
  ugit::getTypeAndRemoveType(type, content);
  ASSERT_EQ(type, "12234");
  ASSERT_EQ(content, "22");

  type.clear();
  content = "       22";
  ugit::getTypeAndRemoveType(type, content);
  ASSERT_EQ(type, "");
  ASSERT_EQ(content, "      22");

  type.clear();
  content = "blob \x00 mm";
  ugit::getTypeAndRemoveType(type, content);
  ASSERT_EQ(type, "blob");
  ASSERT_EQ(content, "\x00 mm");
}
