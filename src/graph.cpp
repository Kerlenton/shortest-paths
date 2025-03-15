#include "graph.hpp"

#include <queue>

void Graph::loadFromStream(std::istream &in) {
    if (!(in >> verticesCount)) {
        throw std::runtime_error("Error reading the number of vertices");
    }
    if (!(in >> edgesCount)) {
        throw std::runtime_error("Error reading the number of edges");
    }
    // Initialize the adjacency list.
    adjList.assign(verticesCount, std::vector<int>{});

    // Read the edges.
    for (int i = 0; i < edgesCount; ++i) {
        int u, v;
        if (!(in >> u >> v)) {
            throw std::runtime_error("Error reading an edge");
        }
        if (u < 0 || u >= verticesCount || v < 0 || v >= verticesCount)
            throw std::out_of_range("Incorrect vertex number");
        // The graph is undirected, so add an edge to both sides.
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
}

std::vector<int> Graph::shortestDistances(int start) const {
    if (start < 0 || start >= verticesCount) {
        throw std::out_of_range("Неверный номер стартовой вершины");
    }

    std::vector<int> distances(verticesCount,
                               -1);  // -1 means that the vertex is not reached.
    std::queue<int> queue;
    distances[start] = 0;
    queue.push(start);

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();

        for (int neighbor : adjList[current]) {
            if (distances[neighbor] == -1) {  // not visited.
                distances[neighbor] = distances[current] + 1;
                queue.push(neighbor);
            }
        }
    }
    return distances;
}
