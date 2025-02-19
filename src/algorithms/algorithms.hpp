#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <chrono>
#include <queue>
#include <deque>

#include "../graph/graph.hpp"

#define inf                                                                                                            \
    10000 // Infinity value for all algorithms (Is it bad due to templates
          // architecture?)

namespace algorithms {

/// @brief Ford Bellman algorithm for SSSP
/// @tparam T type for graph's weights and distances
/// @param startIndex start index for the SSSP
/// @param graph graph itself
/// @param distances vector of distances from start point to all others
template <typename T, typename K>
void FordBellman(size_t startIndex, GeneralGraph<T, K> *graph, std::vector<T> &distances) {
    const auto size = graph->getSize();

    distances.resize(size);
    std::fill(distances.begin(), distances.end(), inf);

    distances[startIndex] = 0;
    std::queue<size_t> q;
    std::vector<int> inQueue(size, 0);
    inQueue[startIndex] = 1;
    q.push(startIndex);

    while (!q.empty()) {
        size_t v = q.front();
        q.pop();
        inQueue[v] = 0;

        auto node = graph->getNode(v);

        for (auto [neighbour, edgeIndex] : node->getNeighbours()) {
            size_t x = neighbour->getIndex();
            auto w = graph->getEdge(edgeIndex)->getWeight();
            if (distances[v] + w < distances[x]) {
                distances[x] = distances[v] + w;
                if (!inQueue[x]) {
                    inQueue[x] = 1;
                    q.push(x);
                }
            }
        }
    }
}

/// @brief Ford Bellman algorithm for SSSP
/// @tparam T type for graph's weights and distances
/// @param startIndex start index for the SSSP
/// @param graph graph itself
/// @param distances vector of distances from start point to all others
template <typename T, typename K>
void DFS_Rec(const GeneralNode<T> *node, const GeneralGraph<T, K> *graph, std::vector<T> &distances) {
    for (const std::pair<GeneralNode<T> *, size_t> &node_and_index :
         graph->getNode(node->getIndex())->getNeighbours()) {
        if (distances[node_and_index.first->getIndex()] == inf) {
            distances[node_and_index.first->getIndex()] =
                distances[node->getIndex()] + graph->getEdge(node_and_index.second)->getWeight();
            DFS_Rec(node_and_index.first, graph, distances);
        }
    }
}

/// @brief Ford Bellman algorithm for SSSP
/// @tparam T type for graph's weights and distances
/// @param startIndex start index for the SSSP
/// @param graph graph itself
/// @param distances vector of distances from start point to all others
template <typename T, typename K> void DFS(size_t startIndex, GeneralGraph<T, K> *graph, std::vector<T> &distances) {
    const auto size = graph->getSize();

    distances.resize(size);
    std::fill(distances.begin(), distances.end(), inf);
    distances[startIndex] = 0;

    DFS_Rec(graph->getNode(startIndex), graph, distances);
}

/// @brief BFS algorithm for SSSP
/// @tparam T type for graph's weights and distances
/// @param startIndex start index for the SSSP
/// @param graph graph itself
/// @param distances vector of distances from start point to all others
template <typename T, typename K> void BFS(size_t startIndex, GeneralGraph<T, K> *graph, std::vector<T> &distances) {
    const auto size = graph->getSize();

    distances.resize(size);
    std::fill(distances.begin(), distances.end(), inf);
    std::queue<size_t> horizon;

    distances[startIndex] = 0;
    horizon.push(startIndex);
    while (!horizon.empty()) {
        size_t nodeIndex = horizon.front();
        horizon.pop();
        const GeneralNode<T> *node = graph->getNode(nodeIndex);

        for (const std::pair<GeneralNode<T> *, size_t> &node_and_index : node->getNeighbours()) {
            if (distances[node_and_index.first->getIndex()] == inf) {
                distances[node_and_index.first->getIndex()] =
                    distances[nodeIndex] + graph->getEdge(node_and_index.second)->getWeight();
                horizon.push(node_and_index.first->getIndex());
            }
        }
    }
}

/// @brief BFS algorithm for SSSP with zero edges
/// @tparam T type for graph's weights and distances
/// @param startIndex start index for the SSSP
/// @param graph graph itself
/// @param distances vector of distances from start point to all others
template <typename T, typename K> void BFS_WithZeroEdges(size_t startIndex, GeneralGraph<T, K> *graph, std::vector<T> &distances) {
    const auto size = graph->getSize();

    distances.resize(size);
    std::fill(distances.begin(), distances.end(), inf);
    std::deque<size_t> horizon;

    distances[startIndex] = 0;
    horizon.push_back(startIndex);
    while (!horizon.empty()) {
        size_t nodeIndex = horizon.front();
        horizon.pop_front();
        const GeneralNode<T> *node = graph->getNode(nodeIndex);

        for (const std::pair<GeneralNode<T> *, size_t> &node_and_index : node->getNeighbours()) {
            if (distances[node_and_index.first->getIndex()] == inf) {
                T weight = graph->getEdge(node_and_index.second)->getWeight();
                distances[node_and_index.first->getIndex()] =
                    distances[nodeIndex] + weight;

                if (weight == 0) {
                    horizon.push_front(node_and_index.first->getIndex());
                } else {
                    horizon.push_back(node_and_index.first->getIndex());
                }
            }
        }
    }
}

/// @brief Dijkstra algorithm for SSSP
/// @tparam T type for graph's weights and distances
/// @param startIndex start index for the SSSP
/// @param graph graph itself
/// @param distances vector of distances from start point to all others
template <typename T, typename K>
void Dijkstra(size_t startIndex, GeneralGraph<T, K> *graph, std::vector<T> &distances) {
    const auto size = graph->getSize();

    distances.resize(size);
    std::fill(distances.begin(), distances.end(), inf);
    std::vector<T> a(size, 0);
    distances[startIndex] = 0;
    for (int i = 0; i < size; i++) {
        int v = -1;
        for (int u = 0; u < size; u++)
            if (!a[u] && (v == -1 || distances[u] < distances[v])) {
                v = u;
            }

        a[v] = true;
        for (const std::pair<GeneralNode<T> *, size_t> &node_and_index : graph->getNode(v)->getNeighbours()) {
            distances[node_and_index.first->getIndex()] =
                std::min(distances[node_and_index.first->getIndex()],
                         distances[v] + graph->getEdge(node_and_index.second)->getWeight());
        }
    }
}

}; // namespace algorithms

#endif // ALGORITHMS_HPP
