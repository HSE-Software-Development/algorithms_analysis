#ifndef EDGES_LIST_GRAPH_HPP
#define EDGES_LIST_GRAPH_HPP

#include "edge.hpp"
#include <iostream>


// Graph representation with edges list
template<typename WeightType>
struct EdgesListGraph {
    std::vector<Edge<WeightType>> edges;

    EdgesListGraph() {}

    EdgesListGraph(const std::vector<Edge<WeightType>> &edges) : edges(edges) {
    }


    void serialize(std::ostream &stream) {
        stream << edges.size() << '\n';
        for (const Edge<WeightType> &edge : edges) {
            stream << edge.fromIndex << " --> " << edge.toIndex << " w: " << edge.weight << '\n';
        }
    }

    void deserialize(std::istream &stream) {
        size_t numOfEdges;
        stream >> numOfEdges;
        edges = std::vector<Edge<WeightType>>(numOfEdges);
        for (int i = 0; i < numOfEdges; i++) {
            std::string separator;
            stream >> edges[i].fromIndex >> separator >> edges[i].toIndex >> separator >> edges[i].weight;
        }

    }
};


#endif
