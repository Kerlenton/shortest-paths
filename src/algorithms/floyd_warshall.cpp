#include "floyd_warshall.hpp"

#include <limits>
#include <span>
#include <stdexcept>
#include <vector>

#include "graph.hpp"

namespace NShortestPaths {

std::vector<int> TFloydWarshall::Compute(const TGraph& graph, int start) const {
    int n = graph.VerticesCount();
    // Validate the starting vertex.
    if (start < 0 || start >= n) {
        throw std::out_of_range("Invalid starting vertex");
    }

    // Define a large value for infinity.
    constexpr int INF = std::numeric_limits<int>::max() / 2;
    // Initialize the distance matrix with INF.
    std::vector<std::vector<int>> dist(n, std::vector<int>(n, INF));
    for (int i = 0; i < n; ++i) {
        // Distance from a vertex to itself is zero.
        dist[i][i] = 0;
    }

    // Set initial distances based on the graph's adjacency list.
    const auto adj = graph.AdjacencyList();
    for (int u = 0; u < n; ++u) {
        for (const auto& v : adj[u]) {
            // Direct edge has a weight of 1.
            dist[u][v] = 1;
        }
    }

    // Use the Floyd–Warshall algorithm to compute all pairs shortest paths.
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    // Prepare the result vector for distances from the starting vertex.
    std::vector<int> result(n, -1);
    for (int i = 0; i < n; ++i)
        if (dist[start][i] < INF) result[i] = dist[start][i];

    return result;
}

}  // namespace NShortestPaths
