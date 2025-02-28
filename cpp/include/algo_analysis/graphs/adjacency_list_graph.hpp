#ifndef ADJACENCY_LIST_GRAPH_HPP
#define ADJACENCY_LIST_GRAPH_HPP

#include "edge.hpp"
#include <unordered_set>


// Graph representation with adjacency list
template<typename WeightType>
struct AdjacencyListGraph {
    using Edge = Edge<WeightType>;

    std::vector<std::vector<Edge>> neighbors;

    AdjacencyListGraph() {

    }

    AdjacencyListGraph(const std::vector<Edge> &edges) {
        size_t maxIndex = 0;
        for (const Edge &edge : edges) {
            maxIndex = std::max(maxIndex, edge.fromIndex);
            maxIndex = std::max(maxIndex, edge.toIndex);
        }

        neighbors.resize(maxIndex + 1, std::vector<Edge>());

        for (const Edge &edge : edges) {
            neighbors[edge.fromIndex].push_back(edge);
        }
    }
};


#endif