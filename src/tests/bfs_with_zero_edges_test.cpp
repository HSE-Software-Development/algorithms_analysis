#include "tests.hpp"

// Demonstrate some basic assertions.
TEST(BFS_WithZeroEdges, Graph1) {
    std::unique_ptr<Graph> graph_1 = std::make_unique<Graph>("../../.cache/graph_example_4.txt");

    std::cout << graph_1.get()->getSize() << std::endl;

    FunctionType<int, int>::Type f = algorithms::BFS_WithZeroEdges<int, int>;

    std::vector<Graph *> graphs;

    graphs.push_back(graph_1.get());
    SSSP<int, int> task(graphs, {0}, f);

    task.run();

    std::vector<std::vector<int>> right_distances = {{0, 10, 20, 40, 80}};

    std::cout << task.getDistances().size() << std::endl;
    for (int i = 0; i < task.getDistances().size(); i++) {
        for (int j = 0; j < task.getDistances()[i].size(); j++) {
            EXPECT_EQ(task.getDistances()[i][j], right_distances[i][j]);
        }
    }
}

