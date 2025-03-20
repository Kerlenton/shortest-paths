#include "graph_factory.hpp"

#include <algorithm>
#include <random>
#include <sstream>

namespace NShortestPaths {
namespace NGraphFactory {

std::vector<std::pair<int, int>> GenerateTree(int n) {
    // Create a list of vertex indices.
    std::vector<int> vertices(n);
    for (int i = 0; i < n; ++i) {
        vertices[i] = i;
    }

    // Use fixed seed for reproducibility.
    std::mt19937 g(42);
    std::shuffle(vertices.begin(), vertices.end(), g);

    // Generate a tree by connecting each vertex with a previous vertex.
    std::vector<std::pair<int, int>> edges;
    for (int i = 1; i < n; ++i) {
        std::uniform_int_distribution<int> dist(0, i - 1);
        int j = dist(g);
        int u = vertices[i], v = vertices[j];
        // Ensure consistent ordering.
        if (u > v) std::swap(u, v);
        edges.push_back({u, v});
    }

    return edges;
}

std::string SerializeGraph(int n,
                           const std::vector<std::pair<int, int>>& edges) {
    // Serialize the graph to a string in the expected format.
    std::ostringstream oss;
    // Write the number of vertices.
    oss << n << "\n";
    // Write the number of edges.
    oss << edges.size() << "\n";
    for (const auto& [u, v] : edges) {
        // Write each edge.
        oss << u << " " << v << "\n";
    }

    return oss.str();
}

}  // namespace NGraphFactory
}  // namespace NShortestPaths
