#include "floyd_warshall_parallel.hpp"

#include <algorithm>
#include <limits>
#include <span>
#include <stdexcept>
#include <thread>
#include <vector>

#include "graph.hpp"

namespace NShortestPaths {

std::vector<int> TFloydWarshallParallel::Compute(const TGraph &graph,
                                                 int start) const {
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
        for (const auto &v : adj[u]) {
            // Direct edge has a weight of 1.
            dist[u][v] = 1;
        }
    }

    // Determine the number of threads to use.
    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) {
        numThreads = 2;
    }

    // Run the Floyd–Warshall algorithm with parallel inner loops.
    for (int k = 0; k < n; ++k) {
        std::vector<std::thread> threads;
        int chunkSize = (n + numThreads - 1) / numThreads;
        for (unsigned int t = 0; t < numThreads; t++) {
            int i_start = t * chunkSize;
            if (i_start >= n) break;
            int i_end = std::min(i_start + chunkSize, n);
            threads.emplace_back([&, i_start, i_end, k]() {
                for (int i = i_start; i < i_end; ++i) {
                    for (int j = 0; j < n; ++j) {
                        if (dist[i][k] + dist[k][j] < dist[i][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                        }
                    }
                }
            });
        }

        // Join all threads for this iteration.
        for (auto &th : threads) {
            th.join();
        }
    }

    // Prepare the result vector for distances from the starting vertex.
    std::vector<int> result(n, -1);
    for (int i = 0; i < n; ++i) {
        if (dist[start][i] < INF) {
            result[i] = dist[start][i];
        }
    }

    return result;
}

}  // namespace NShortestPaths
