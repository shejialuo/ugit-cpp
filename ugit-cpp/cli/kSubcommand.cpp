/**
 * @file kSubcommand.cpp
 * @author shejialuo
 *
 */

#include "kSubcommand.hpp"

#include "base.hpp"
#include "data.hpp"
#include "util.hpp"

#include <cstdio>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

/**
 * @brief Set up k subcommand
 *
 * @param app CLI::App
 */
void ugit::setKSubcommand(CLI::App &app) {
  auto *k = app.add_subcommand("k", "visualization all refs and all the commits pointed by the refs");
  k->callback([]() { ugit::runKSubcommand(); });
}

/**
 * @brief run k subcommand
 *
 */
void ugit::runKSubcommand() {
  std::unordered_map<std::string, ugit::RefContainer> refMap{};
  std::queue<std::string> commitIDs{};
  std::unordered_set<std::string> visited{};

  std::string dotCommand{"digraph commits {\n"};
  // Here, we should not deference the symbol, because we want to
  // display the symbol points to which object. If we dereference
  // the symbol, we don't know which HEAD points to which symbol
  // Instead, we will get the picture where HEAD points to some
  // RAW hash object id.
  ugit::iterateRefs(refMap, false);
  for (auto &ref : refMap) {
    dotCommand += "\"" + ref.first + "\"" + " [shape=note]\n";
    dotCommand += "\"" + ref.first + "\"" + " -> " + "\"" + ref.second.value + "\"" + "\n";
    if (!ref.second.symbolic) {
      commitIDs.push(ref.second.value);
    }
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
    std::string parentCommitID = commitContent.parentCommitID;
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
