#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <queue>

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
} // namespace algorithms

#endif // ALGORITHMS_HPP
