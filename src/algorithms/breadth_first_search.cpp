#include "breadth_first_search.hpp"

#include <queue>
#include <span>
#include <stdexcept>
#include <vector>

#include "graph.hpp"

namespace NShortestPaths {

std::vector<int> TBreadthFirstSearch::Compute(const TGraph& graph,
                                              int start) const {
    int n = graph.VerticesCount();
    // Validate the starting vertex.
    if (start < 0 || start >= n) {
        throw std::out_of_range("Invalid starting vertex");
    }

    // Initialize distances with -1 to indicate unvisited vertices.
    std::vector<int> distances(n, -1);
    // Create a queue for BFS.
    std::queue<int> queue;
    // Distance to the starting vertex is 0.
    distances[start] = 0;
    // Enqueue the starting vertex.
    queue.push(start);

    // Perform BFS.
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        // Visit each neighbor of the current vertex.
        for (const auto& v : graph.AdjacencyList()[u]) {
            // If the neighbor has not been visited.
            if (distances[v] == -1) {
                // Update distance.
                distances[v] = distances[u] + 1;
                // Enqueue the neighbor.
                queue.push(v);
            }
        }
    }

    return distances;
}

}  // namespace NShortestPaths
