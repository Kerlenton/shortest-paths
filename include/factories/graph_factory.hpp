#pragma once

#include <string>
#include <utility>
#include <vector>

namespace NShortestPaths {
namespace NGraphFactory {

std::vector<std::pair<int, int>> GenerateTree(int n);
std::string SerializeGraph(int n,
                           const std::vector<std::pair<int, int>>& edges);

}  // namespace NGraphFactory
}  // namespace NShortestPaths
