#ifndef DIJKSTRA_WITH_FIB_HPP
#define DIJKSTRA_WITH_FIB_HPP


#include <algo_analysis/algorithms/algorithm.hpp>
#include <algo_analysis/graphs/adjacency_list_graph.hpp>
#include <boost/heap/fibonacci_heap.hpp>
#include <iostream>
#include <algorithm>
#include <queue>

// Dijkstra's algorithm
template<typename WeightType> 
struct DijkstraWithFibAlgorithm : public Algorithm<WeightType> {
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

    struct Node {
        size_t vertex;
        WeightType distance;
    
        bool operator>(const Node& other) const {
            return distance > other.distance;
        }
    };    

    
    std::vector<WeightType> distances; // Distances from the start node
    Graph graph;

    DijkstraWithFibAlgorithm() {

    }

    WeightType inf;
    
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
        int n = graph.nodesNumber;
        distances = std::vector<WeightType>(n, inf);
        distances[startIndex] = 0;
        
        boost::heap::fibonacci_heap<Node, boost::heap::compare<std::greater<Node>>> q;
        q.push({ startIndex, 0 });

        while (!q.empty()) {
            auto [ u, dist ] = q.top();
            q.pop();

            if (dist > distances[u]) continue;

            for (const Edge& edge : graph.neighbors[u]) {
                size_t v = edge.toIndex;
                WeightType newDist = distances[u] + edge.weight;

                if (newDist < distances[v]) {
                    distances[v] = newDist;
                    q.push({ v, newDist });
                }
            }
        }
        
        return distances;
    }

};



#endif
