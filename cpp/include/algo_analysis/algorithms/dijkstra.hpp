#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP


#include <algo_analysis/algorithms/algorithm.hpp>
#include <algo_analysis/graphs/adjacency_list_graph.hpp>
#include <iostream>
#include <queue>

template<typename WeightType> 
struct DijkstraAlgorithm : public Algorithm<WeightType> {
    using Edge = Edge<WeightType>;

    struct Graph : public AdjacencyListGraph<WeightType> {
        using BaseClass = AdjacencyListGraph<WeightType>;

        struct Node {
            bool isVisited;
        };

        size_t nodesNumber;
        std::vector<Node> nodes;

        Graph() : BaseClass() {

        }

        Graph(const std::vector<Edge> &edges): BaseClass(edges)  {
            nodesNumber = BaseClass::neighbors.size();
            nodes.resize(nodesNumber, {false});
        }
    };

    
    std::vector<WeightType> distances;
    Graph graph;

    DijkstraAlgorithm() {

    }

    WeightType inf;
    
    void fit(const EdgesListGraph<WeightType> &graph_) override {
        graph = Graph(graph_.edges);
        inf = 1;
        for (const Edge &edge : graph_.edges) {
            inf += edge.weight;
        }
    }

    std::vector<WeightType> computeDistances(size_t startIndex) override {
        distances = std::vector<WeightType>(graph.neighbors.size(), inf);
        distances[startIndex] = 0;
        for (int i = 0; i < graph.neighbors.size(); i++) {
            int v = -1;
            for (int u = 0; u < graph.neighbors.size(); u++)
                if (!graph.nodes[u].isVisited && (v == -1 || distances[u] < distances[v])) {
                    v = u;
                }

            graph.nodes[v].isVisited = true;
            for (const Edge& edge : graph.neighbors[v]) {
                distances[edge.toIndex] = std::min(
                    distances[edge.toIndex],
                    distances[v] + edge.weight
                );
            }
        }
        return distances;
    }

};



#endif
