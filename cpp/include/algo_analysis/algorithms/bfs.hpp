#ifndef BFS_HPP
#define BFS_HPP


#include <algo_analysis/algorithms/algorithm.hpp>
#include <algo_analysis/graphs/adjacency_list_graph.hpp>
#include <iostream>
#include <queue>

template<typename WeightType> 
struct BFSAlgorithm : public Algorithm<WeightType> {
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

    BFSAlgorithm() {

    }
    
    void fit(const EdgesListGraph<WeightType> &graph_) override {
        graph = Graph(graph_.edges);
        distances = std::vector<WeightType>(graph.neighbors.size());
    }

    std::vector<WeightType> computeDistances(size_t startIndex) override {
        std::queue<size_t> hor;
        hor.push(startIndex);
        distances[startIndex] = 0;
        while (!hor.empty()) {
            size_t v = hor.front();
            hor.pop();

            for (const Edge &edge : graph.neighbors[v]) {
                size_t u = edge.toIndex;
                if (!graph.nodes[u].isVisited) {
                    graph.nodes[u].isVisited = true;
                    distances[u] = distances[v] + edge.weight;
                    hor.push(u);
                }
            }
        }
        return distances;
    }

};



#endif
