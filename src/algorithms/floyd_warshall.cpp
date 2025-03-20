#include "floyd_warshall.hpp"

#include <limits>
#include <span>
#include <stdexcept>
#include <vector>

#include "graph.hpp"

namespace NShortestPaths {

std::vector<int> TFloydWarshall::Compute(const TGraph& graph, int start) const {
    int n = graph.VerticesCount();
    if (start < 0 || start >= n) {
        throw std::out_of_range("Invalid starting vertex");
    }

    constexpr int INF = std::numeric_limits<int>::max() / 2;
    std::vector<std::vector<int>> dist(n, std::vector<int>(n, INF));
    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
    }

    const auto adj = graph.AdjacencyList();
    for (int u = 0; u < n; ++u) {
        for (int v : adj[u]) {
            dist[u][v] = 1;
        }
    }

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    std::vector<int> result(n, -1);
    for (int i = 0; i < n; ++i)
        if (dist[start][i] < INF) result[i] = dist[start][i];

    return result;
}

}  // namespace NShortestPaths
