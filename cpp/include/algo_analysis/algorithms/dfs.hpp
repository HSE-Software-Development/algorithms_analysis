#ifndef DFS_HPP
#define DFS_HPP


#include <algo_analysis/algorithms/algorithm.hpp>
#include <algo_analysis/graphs/adjacency_list_graph.hpp>
#include <iostream>

// Depth-first search algorithm
template<typename WeightType> 
struct DFSAlgorithm : public Algorithm<WeightType> {

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

        Graph(const std::vector<Edge<WeightType>> &edges): BaseClass(edges)  {
            nodesNumber = BaseClass::neighbors.size();
            nodes = std::vector<Node>(nodesNumber, {false});
        }
    };

    
    std::vector<WeightType> distances; // Distances from the start node
    Graph graph;

    DFSAlgorithm() {

    }
    
    // Fit the algorithm to the graph
    void fit(const EdgesListGraph<WeightType> &graph_) override {
        graph = Graph(graph_.edges);
    }


    // Compute distances from the start node
    void dfs(size_t v) {
        for (const Edge<WeightType> &edge : graph.neighbors[v]) {
            size_t u = edge.toIndex;
            if (!graph.nodes[u].isVisited) {
                graph.nodes[u].isVisited = true;
                distances[u] = distances[v] + edge.weight;
                dfs(u);
            }
        }
    }

    // Compute distances from the start node
    std::vector<WeightType> computeDistances(size_t startIndex) override {
        distances = std::vector<WeightType>(graph.neighbors.size(), -1);
        for (auto &node : graph.nodes) {
            node.isVisited = false;
        }
        graph.nodes[startIndex].isVisited = true;
        distances[startIndex] = 0;
        dfs(startIndex);
        return distances;
    }

};



#endif