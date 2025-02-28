#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <algo_analysis/graphs/edges_list_graph.hpp>
#include <vector>


template<typename WeightType> 
struct Algorithm {
    virtual void fit(const EdgesListGraph<WeightType> &graph) = 0;
    virtual std::vector<WeightType> computeDistances(size_t startIndex) = 0;
};

#endif

