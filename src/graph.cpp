#include "graph.hpp"

#include <queue>
#include <ranges>
#include <stdexcept>

void Graph::LoadFromStream(std::istream &in) {
    if (!(in >> VerticesCount_)) [[unlikely]] {
        throw std::runtime_error("Error reading the number of vertices");
    }
    if (!(in >> EdgesCount_)) [[unlikely]] {
        throw std::runtime_error("Error reading the number of edges");
    }

    // Initialize the adjacency list.
    AdjList_.assign(VerticesCount_, std::vector<int>{});
    for ([[maybe_unused]] int i : std::views::iota(0, EdgesCount_)) {
        int u, v;
        if (!(in >> u >> v)) [[unlikely]] {
            throw std::runtime_error("Error reading an edge");
        }
        if (u < 0 || u >= VerticesCount_ || v < 0 || v >= VerticesCount_)
            [[unlikely]]
            throw std::out_of_range("Incorrect vertex number");
        // The graph is undirected, so add an edge to both sides.
        AdjList_[u].push_back(v);
        AdjList_[v].push_back(u);
    }
}

std::vector<int> Graph::ShortestDistances(int start) const {
    if (start < 0 || start >= VerticesCount_) [[unlikely]] {
        throw std::out_of_range("Invalid starting vertex number");
    }

    std::vector<int> distances(VerticesCount_,
                               -1);  // -1 means that the vertex is not reached.
    std::queue<int> queue;
    distances[start] = 0;
    queue.push(start);

    // BFS.
    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();

        for (int neighbor : AdjList_[current]) {
            if (distances[neighbor] == -1) {  // Not visited.
                distances[neighbor] = distances[current] + 1;
                queue.push(neighbor);
            }
        }
    }
    return distances;
}
