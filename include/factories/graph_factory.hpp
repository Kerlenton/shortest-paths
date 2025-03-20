#pragma once

#include <string>
#include <utility>
#include <vector>

namespace NShortestPaths {
namespace NGraphFactory {

// Generate a random tree with n vertices.
std::vector<std::pair<int, int>> GenerateTree(int n);
// Serialize the graph to a string format that can be read by the program.
std::string SerializeGraph(int n,
                           const std::vector<std::pair<int, int>>& edges);

}  // namespace NGraphFactory
}  // namespace NShortestPaths
