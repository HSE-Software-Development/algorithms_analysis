#ifndef FORD_BELLMAN_HPP
#define FORD_BELLMAN_HPP


#include <algo_analysis/algorithms/algorithm.hpp>
#include <algo_analysis/graphs/adjacency_list_graph.hpp>
#include <iostream>
#include <queue>

// Ford-Bellman algorithm
template<typename WeightType> 
struct FordBellmanAlgorithm : public Algorithm<WeightType> {
    using Edge = Edge<WeightType>;

    // Graph representation
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

    
    std::vector<WeightType> distances; // Distances from the start node
    std::vector<bool> inQueue;
    Graph graph;
    WeightType inf;

    FordBellmanAlgorithm() {

    }
    
    // Fit the algorithm to the graph
    void fit(const EdgesListGraph<WeightType> &graph_) override {
        graph = Graph(graph_.edges);
        inf = 1;
        for (const Edge &edge : graph_.edges) {
            inf += edge.weight;
        }
    }


    // Compute distances from the start node
    std::vector<WeightType> computeDistances(size_t startIndex) override {
        distances = std::vector<WeightType>(graph.neighbors.size(), inf);
        inQueue = std::vector<bool>(graph.neighbors.size(), false);
        distances[startIndex] = 0;
        std::queue<size_t> hor;
        hor.push(startIndex);

        while (!hor.empty()) {
            size_t v = hor.front();
            hor.pop();
            inQueue[v] = 0;

            for (const Edge &edge : graph.neighbors[v]) {
                if (distances[v] + edge.weight < distances[edge.toIndex]) {
                    distances[edge.toIndex] = distances[v] + edge.weight;
                    if (!inQueue[edge.toIndex]) {
                        inQueue[edge.toIndex] = true;
                        hor.push(edge.toIndex);
                    }
                }
            }
        }

        for (int i = 0; i < distances.size(); i++) {
            distances[i] = distances[i] == inf ? -1 : distances[i];
        }
        return distances;
    }

};



#endif
