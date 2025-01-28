#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <memory>
#include <unordered_map>
#include <vector>

// Graph node class
template <typename T> class GeneralNode {
private:
  std::vector<std::pair<GeneralNode<T> *, size_t>> neighbors; // Node neighbors vector
  T value;          // Value of the node

public:
  /// @brief Default class contructor
  GeneralNode() { neighbors = nullptr; }

  /// @brief Class constructor
  /// @param edgeIndex_ new index of the edge this node is from
  /// @param value_ new value of the node
  GeneralNode(T value_) {
    value = value_;
    neighbors.reserve(16);
  }

  /// @brief Getter of the all node's neighbors
  /// @return const link to the node's neighbors vector
  const std::vector<std::pair<GeneralNode<T> *, size_t>> &getNeighbours() const { return neighbors; }

  /// @brief Getter of the node's value
  /// @return Value of the node
  T getValue() const { return value; }

  /// @brief Setter of the node's value
  /// @param value_ new value of the node
  void setValue(const T &value_) { value = value_; }

  /// @brief Add neighbour to the node
  /// @param neighbour new node's neighbour
  /// @param edgeIndex index of the edge between the node and its neighbour
  void addNeighbour(const GeneralNode<T> *neighbour, size_t edgeIndex) {
    neighbors.emplace_back((neighbour, edgeIndex));
  }

  /// @brief Class destructor
  ~GeneralNode() {}
}; // End of class 'GeneralNode'

template <typename T> class GeneralEdge {
private:
  size_t start, end; // Edge's ends
  T weight;          // Edge's weight

public:
  /// @brief Class default constructor
  GeneralEdge() { start = end = nullptr; }

  /// @brief Class constructor
  /// @param start_ new edge's start
  /// @param end_ new edge's end
  /// @param weight_ new edge's weight
  GeneralEdge(size_t start_, size_t end_, T weight_) {
    start = start_;
    end = end_;
    weight = weight_;
  }

  /// @brief Getter of the edge's weight
  /// @return Weight of the edge
  T getWeight() const { return weight; }

  /// @brief Getter of the edge's start node index
  /// @return Start node index of the edge
  size_t getStart() const { return start; }

  /// @brief Getter of the edge's end node index
  /// @return End node index of the edge
  size_t getEnd() const { return end; }

  /// @brief Setter of the edge's weight
  /// @param weight_ new weight of the edge
  void setWeight(T weight_) { weight = weight_; }

  /// @brief Class destructor
  ~GeneralEdge() {}
}; // End of class 'GeneralEdge'

// Graph class
template <typename T, typename K> class Graph {
private:
  std::vector<std::unique_ptr<GeneralEdge<T>>> edges; // All edges of the graph
  std::vector<std::unique_ptr<GeneralNode<K>>> nodes; // All nodes of the graph

public:
  /// @brief Class constructor
  /// @param inputStream input stream with graph's data
  Graph(std::istream &inputStream = std::cin) {}

  /// @brief Class constructor
  /// @param filePath path to the file with graph data (text format)
  Graph(const std::string &filePath);

  /// @brief Getter of graph's edge by its index
  /// @param index index of the grap's edge
  /// @return Non-owning pointer to the edge in the graph
  const GeneralEdge<T> *getEdge(size_t index) const {
    if (index >= edges.size()) {
      return nullptr;
    }
    return edges[index].get();
  }

  /// @brief Getter of graph's node by its index
  /// @param index index of the grap's node
  /// @return Non-owning pointer to the node in the graph
  const GeneralNode<K> *getNode(size_t index) const {
    if (index >= nodes.size()) {
      return nullptr;
    }
    return nodes[index].get();
  }

  /// @brief Get graph's size
  /// @return size of the graph
  size_t getSize() const { return nodes.size(); }

  /// @brief Class destrutor
  ~Graph() {}
}; // End of class 'Graph'

#endif // GRAPH_HPP
