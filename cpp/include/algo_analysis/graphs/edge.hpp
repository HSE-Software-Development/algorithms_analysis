#ifndef EDGE_HPP
#define EDGE_HPP


#include <vector>


template<typename WeightType>
struct Edge {
    size_t fromIndex;
    size_t toIndex;
    WeightType weight;
};


#endif