#ifndef DFS_HPP
#define DFS_HPP


#include <algo_analysis/algorithms/algorithm.hpp>
#include <algo_analysis/graphs/adjacency_list_graph.hpp>
#include <iostream>

template<typename WeightType> 
struct DFSAlgorithm : public Algorithm<WeightType> {

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

    
    std::vector<WeightType> distances;
    Graph graph;

    DFSAlgorithm() {

    }
    
    void fit(const EdgesListGraph<WeightType> &graph_) override {
        graph = Graph(graph_.edges);
    }


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