#include "breadth_first_search.hpp"

#include <queue>
#include <stdexcept>

namespace NShortestPaths {

std::vector<int> TBreadthFirstSearch::Compute(const TGraph& graph,
                                              int start) const {
    int n = graph.VerticesCount();
    if (start < 0 || start >= n) {
        throw std::out_of_range("Invalid starting vertex");
    }
    std::vector<int> distances(n, -1);
    std::queue<int> queue;
    distances[start] = 0;
    queue.push(start);
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        for (int v : graph.AdjacencyList()[u]) {
            if (distances[v] == -1) {
                distances[v] = distances[u] + 1;
                queue.push(v);
            }
        }
    }
    return distances;
}

}  // namespace NShortestPaths