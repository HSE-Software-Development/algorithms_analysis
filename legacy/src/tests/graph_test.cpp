#include "tests.hpp"

TEST(GeneralNodeTest, Constructor) {
    size_t index = 3;
    int value = 42;
    size_t capacity = 8;
    GeneralNode<int> node(index, value, capacity);

    EXPECT_EQ(node.getIndex(), index);
    EXPECT_EQ(node.getValue(), value);
    int newValue = 30;
    node.setValue(newValue);
    EXPECT_EQ(node.getValue(), newValue);
}

TEST(GeneralNodeTest, AddNeighbour) {
    GeneralNode<int> node1(0, 16);
    GeneralNode<int> node2(1, 16);

    size_t edgeIndex = 0;
    node1.addNeighbour(&node2, edgeIndex);

    const auto &neighbours = node1.getNeighbours();
    EXPECT_EQ(neighbours.size(), 1);
    EXPECT_EQ(neighbours[0].first->getIndex(), 1);
    EXPECT_EQ(neighbours[0].second, edgeIndex);
}

TEST(GeneralEdge, Constructor) {
    size_t start = 2;
    size_t end = 3;
    int weight = 7;

    GeneralEdge<int> edge(start, end, weight);
    EXPECT_EQ(edge.getStart(), start);
    EXPECT_EQ(edge.getEnd(), end);
    EXPECT_EQ(edge.getWeight(), weight);

    int newWeight = 10;
    edge.setWeight(newWeight);
    EXPECT_EQ(edge.getWeight(), newWeight);
}

TEST(GeneralGraphTest, ConstructorFromFile) {
    const std::string filePath = "../../.cache/graph_example_4.txt";
    std::unique_ptr<GeneralGraph<int, int>> graph = std::make_unique<GeneralGraph<int, int>>(filePath);

    EXPECT_EQ(graph->getSize(), 5);

    for (size_t i = 0; i < 5; ++i) {
        const GeneralNode<int> *node = graph->getNode(i);
        ASSERT_NE(node, nullptr);
        EXPECT_EQ(node->getIndex(), i);
    }

    // Ребро 0 -> 1 с весом 10
    const GeneralEdge<int> *edge0 = graph->getEdge(0);
    ASSERT_NE(edge0, nullptr);
    EXPECT_EQ(edge0->getStart(), 0);
    EXPECT_EQ(edge0->getEnd(), 1);
    EXPECT_EQ(edge0->getWeight(), 10);

    // Ребро 0 -> 2 с весом 20
    const GeneralEdge<int> *edge1 = graph->getEdge(1);
    ASSERT_NE(edge1, nullptr);
    EXPECT_EQ(edge1->getStart(), 0);
    EXPECT_EQ(edge1->getEnd(), 2);
    EXPECT_EQ(edge1->getWeight(), 20);

    // Ребро 1 -> 3 с весом 30
    const GeneralEdge<int> *edge2 = graph->getEdge(2);
    ASSERT_NE(edge2, nullptr);
    EXPECT_EQ(edge2->getStart(), 1);
    EXPECT_EQ(edge2->getEnd(), 3);
    EXPECT_EQ(edge2->getWeight(), 30);

    // Ребро 3 -> 4 с весом 40
    const GeneralEdge<int> *edge3 = graph->getEdge(3);
    ASSERT_NE(edge3, nullptr);
    EXPECT_EQ(edge3->getStart(), 3);
    EXPECT_EQ(edge3->getEnd(), 4);
    EXPECT_EQ(edge3->getWeight(), 40);

    EXPECT_EQ(graph->getEdge(4), nullptr);
}

TEST(GeneralGraphTest, NeighborsCheck) {
    const std::string filePath = "../../.cache/graph_example_4.txt";
    std::unique_ptr<GeneralGraph<int, int>> graph = std::make_unique<GeneralGraph<int, int>>(filePath);

    const GeneralNode<int> *node0 = graph->getNode(0);
    ASSERT_NE(node0, nullptr);
    const auto &neighbors0 = node0->getNeighbours();
    EXPECT_EQ(neighbors0.size(), 2);
    EXPECT_EQ(neighbors0[0].first->getIndex(), 1);
    EXPECT_EQ(neighbors0[0].second, 0);
    EXPECT_EQ(neighbors0[1].first->getIndex(), 2);
    EXPECT_EQ(neighbors0[1].second, 1);

    const GeneralNode<int> *node1 = graph->getNode(1);
    ASSERT_NE(node1, nullptr);
    const auto &neighbors1 = node1->getNeighbours();
    EXPECT_EQ(neighbors1.size(), 2);
    EXPECT_EQ(neighbors1[0].first->getIndex(), 0);
    EXPECT_EQ(neighbors1[0].second, 0);
    EXPECT_EQ(neighbors1[1].first->getIndex(), 3);
    EXPECT_EQ(neighbors1[1].second, 2);

    const GeneralNode<int> *node3 = graph->getNode(3);
    ASSERT_NE(node3, nullptr);
    const auto &neighbors3 = node3->getNeighbours();
    EXPECT_EQ(neighbors3.size(), 2);
    EXPECT_EQ(neighbors3[0].first->getIndex(), 1);
    EXPECT_EQ(neighbors3[0].second, 2);
    EXPECT_EQ(neighbors3[1].first->getIndex(), 4);
    EXPECT_EQ(neighbors3[1].second, 3);
}
