#include "graph_factory.hpp"

#include <algorithm>
#include <random>
#include <sstream>

namespace NShortestPaths {
namespace NGraphFactory {

std::vector<std::pair<int, int>> GenerateTree(int n) {
    std::vector<int> vertices(n);
    for (int i = 0; i < n; ++i) {
        vertices[i] = i;
    }
    // Use fixed seed for reproducibility.
    std::mt19937 g(42);
    std::shuffle(vertices.begin(), vertices.end(), g);

    std::vector<std::pair<int, int>> edges;
    for (int i = 1; i < n; ++i) {
        std::uniform_int_distribution<int> dist(0, i - 1);
        int j = dist(g);
        int u = vertices[i], v = vertices[j];
        if (u > v) std::swap(u, v);
        edges.push_back({u, v});
    }
    return edges;
}

std::string SerializeGraph(int n,
                           const std::vector<std::pair<int, int>>& edges) {
    std::ostringstream oss;
    oss << n << "\n";
    oss << edges.size() << "\n";
    for (const auto& edge : edges) {
        oss << edge.first << " " << edge.second << "\n";
    }
    return oss.str();
}

}  // namespace NGraphFactory
}  // namespace NShortestPaths