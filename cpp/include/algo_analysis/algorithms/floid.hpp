#ifndef FLOID_HPP
#define FLOID_HPP

#include <algo_analysis/algorithms/algorithm.hpp>
#include <algo_analysis/graphs/adjacency_list_graph.hpp>
#include <iostream>
#include <queue>

// Floid algorithm
template <typename WeightType>
struct FloidAlgorithm : public Algorithm<WeightType> {
    using Edge = Edge<WeightType>;

    // Graph representation
    struct Graph : public AdjacencyListGraph<WeightType> {
        using BaseClass = AdjacencyListGraph<WeightType>;

        size_t nodesNumber;

        Graph() : BaseClass() {}

        Graph(const std::vector<Edge> &edges): BaseClass(edges)  {
            nodesNumber = BaseClass::neighbors.size();
        }
    };

    
    std::vector<std::vector<WeightType>> distances; // Distances from each node to all the rest
    WeightType inf;
    Graph graph;

    FloidAlgorithm() {

    }
    
    // Fit the algorithm to the graph
    void fit(const EdgesListGraph<WeightType> &graph_) override {
        graph = Graph(graph_.edges);
        inf = 1;
        for (const Edge &edge : graph_.edges) {
            inf += edge.weight;
        }

        distances.resize(graph.nodesNumber, std::vector<WeightType>(graph.nodesNumber, inf));
        for (int v = 0; v < distances.size(); ++v) {
            distances[v][v] = 0;
        }
        for (const Edge &edge : graph_.edges) {
            distances[edge.fromIndex][edge.toIndex] = edge.weight;
        }

        calcDistances();
    }

    // Compute distances from the start node
    std::vector<WeightType> computeDistances(size_t startIndex) override {
        std::vector<WeightType> result = distances[startIndex];
        // mark infinities as unreachable
        for (auto& w : result) {
            if (w >= inf) w = -1;
        }
        return result;
    }

private:
    void calcDistances() {
        int n = distances.size();
        for (int i = 0; i < n; ++i) {
            for (int u = 0; u < n; ++u) {
                for (int v = 0; v < n; ++v) {
                    distances[u][v] = std::min(
                        distances[u][v],
                        distances[u][i] + distances[i][v]
                    );
                }
            }
        }
    }

    /// @brief Just for debugging purposes
    void printDistances() const {
        int n = distances.size();
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                std::cout << distances[u][v] << ' ';
            }
            std::cout << std::endl;
        }
    }
};

#endif