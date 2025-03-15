#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <istream>
#include <stdexcept>

class Graph {
public:
    Graph() = default;

    // Reads the graph from the input stream. 
    void loadFromStream(std::istream &in);

    // Calculates the shortest distances from vertex start using width search.
    // Returns a vector where i-th element is the distance from start to vertex i.
    std::vector<int> shortestDistances(int start) const;

    // Returns the number of vertices in the graph.
    int numVertices() const { return verticesCount; }

private:
    int verticesCount {0};
    int edgesCount {0};
    std::vector<std::vector<int>> adjList;  // Adjacency list.
};

#endif // GRAPH_HPP
