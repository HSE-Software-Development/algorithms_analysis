#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <queue>

#include "../graph/graph.hpp"

#define inf                                                                    \
    10000 // Infinity value for all algorithms (Is it bad due to templates
              // architecture?)

namespace algorithms {
/// @brief Ford Bellman algorithm for SSSP
/// @tparam T type for graph's weights and distances
/// @param startIndex start index for the SSSP
/// @param g graph itself
/// @param distances vector of distances from start point to all others
template <typename T>
void FordBellman(size_t startIndex, GeneralGraph<T, size_t> *g,
                 std::vector<T> &distances) {
    auto size = g->getSize();
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
        auto node = g->getNode(v);
        for (auto [neighbour, edgeIndex] : node->getNeighbours()) {
            size_t x = neighbour->getIndex();
            auto w = g->getEdge(edgeIndex)->getWeight();
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
