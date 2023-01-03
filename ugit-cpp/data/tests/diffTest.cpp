#include "diff.hpp"

#include <gtest/gtest.h>
#include <string>
#include <unordered_map>

TEST(DiffTest, parseTreeContent1) {
  std::string treeContent{"blob 833 a"};
  std::string treeParentContent{"blob 833 a"};
  std::unordered_map<std::string, std::pair<std::string, std::string>> pathToObjectIDs{};
  parseTreeContent(treeContent, pathToObjectIDs, 0);
  parseTreeContent(treeParentContent, pathToObjectIDs, 1);
  EXPECT_EQ(pathToObjectIDs["a"].first, "833");
  EXPECT_EQ(pathToObjectIDs["a"].second, "833");
}

TEST(DiffTest, parseTreeContent2) {
  std::string treeContent{"blob 833 a"};
  std::string treeParentContent{"blob 834 a"};
  std::unordered_map<std::string, std::pair<std::string, std::string>> pathToObjectIDs{};
  parseTreeContent(treeContent, pathToObjectIDs, 0);
  parseTreeContent(treeParentContent, pathToObjectIDs, 1);
  EXPECT_EQ(pathToObjectIDs["a"].first, "833");
  EXPECT_EQ(pathToObjectIDs["a"].second, "834");
}

TEST(DiffTest, parseTreeContent3) {
  std::string treeContent{"blob 833 a\nblob 844 b"};
  std::string treeParentContent{"blob 833 a\nblob 845 b\ntree 132 aaa"};
  std::unordered_map<std::string, std::pair<std::string, std::string>> pathToObjectIDs{};
  parseTreeContent(treeContent, pathToObjectIDs, 0);
  parseTreeContent(treeParentContent, pathToObjectIDs, 1);
  EXPECT_EQ(pathToObjectIDs["a"].first, "833");
  EXPECT_EQ(pathToObjectIDs["a"].second, "833");
  EXPECT_EQ(pathToObjectIDs["b"].first, "844");
  EXPECT_EQ(pathToObjectIDs["b"].second, "845");
  EXPECT_FALSE(pathToObjectIDs.count("aaa"));
}
