#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <algo_analysis/graphs/edges_list_graph.hpp>
#include <vector>

// Abstract class for algorithms
template<typename WeightType> 
struct Algorithm {
    // Fit the algorithm to the graph
    virtual void fit(const EdgesListGraph<WeightType> &graph) = 0;
    // Compute distances from the start node
    virtual std::vector<WeightType> computeDistances(size_t startIndex) = 0;
};

#endif

