/**
 * @file kSubcommand.cpp
 * @author shejialuo
 *
 */

#include "kSubcommand.hpp"

#include "base.hpp"
#include "data.hpp"

#include <cstdio>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

/**
 * @brief Set up k subcommand
 *
 * @param app CLI::App
 */
void ugit::setKSubcommand(CLI::App &app) {
  auto *k = app.add_subcommand("k", "visualization all refs and all the commits pointed by the refs");
  k->callback([]() { ugit::runKSubcommand(); });
}

#include <iostream>
void ugit::runKSubcommand() {
  std::unordered_map<std::string, std::string> refMap{};
  std::queue<std::string> commitIDs{};
  std::unordered_set<std::string> visited{};

  std::string dotCommand{"digraph commits {\n"};
  ugit::iterateRefs(refMap);
  for (auto &ref : refMap) {
    dotCommand += "\"" + ref.first + "\"" + " [shape=note]\n";
    dotCommand += "\"" + ref.first + "\"" + " -> " + "\"" + ref.second + "\"" + "\n";
    commitIDs.push(ref.second);
  }

  while (!commitIDs.empty()) {
    std::string commitID = commitIDs.front();
    dotCommand += "\"" + commitID + "\"" + " [shape=box style=filled label=\"" + commitID + "\"]\n";
    commitIDs.pop();
    if (visited.count(commitID)) {
      continue;
    }
    visited.insert(commitID);
    auto commitContent = ugit::getCommit(commitID);
    std::string parentCommitID = std::get<1>(commitContent);
    if (!parentCommitID.empty()) {
      commitIDs.push(parentCommitID);
      dotCommand += "\"" + commitID + "\" -> " + "\"" + parentCommitID + "\"\n";
    }
  }

  dotCommand += "}";

  // use `popen` to call the children
  FILE *p = popen("dot -Tgtk /dev/stdin ", "w");
  fputs(dotCommand.c_str(), p);
  pclose(p);
}
