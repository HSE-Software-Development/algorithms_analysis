#include <algo_analysis/algorithms/dfs.hpp>
#include <algo_analysis/task.hpp>
#include <algo_analysis/graphs/edges_list_graph.hpp>
#include <algo_analysis/graphs/edge.hpp>

#include <vector>
#include <iostream>


int main() {
    EdgesListGraph<int> graph({
        Edge<int>{0, 1, 10},
        Edge<int>{0, 2, 10},
        Edge<int>{1, 3, 10},
    });


    Task<int> task({0}, graph);

    DFSAlgorithm<int> algo;

    Task<int>::Statistics stats =  task.estimate(algo);
    std::cout << "MU: " << stats.initializationMemoryUsage << "\n";
    std::cout << "IT: " << stats.initializationTime << "\n";

    std::cout << "Hello world!" << "\n";
    
}