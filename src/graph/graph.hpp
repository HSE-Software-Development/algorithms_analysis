#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <fstream>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

// GeneralGraph node class
template <typename T> class GeneralNode {
  private:
    T value;                                                    // Value of the node
    size_t index;                                               // Index of the node
    size_t capacity;                                            // Memory capacity (sizeof(neighbors[0])*capacity bytes)
                                                                // that reserved for push backs
    std::vector<std::pair<GeneralNode<T> *, size_t>> neighbors; // Node neighbors vector

  public:
    /// @brief Default class contructor
    GeneralNode() {
        index = -1;
        capacity = 16;
        neighbors = nullptr;
    }

    /// @brief Class constructor
    /// @param index_ new index of the node
    /// @param capacity_ initial vertex capacity
    GeneralNode(size_t index_, size_t capacity_) {
        index = index_;
        capacity = capacity_;
        neighbors.reserve(capacity);
    }

    /// @brief Class constructor
    /// @param value_ new value of the node
    /// @param index_ new index of the node
    /// @param capacity_ new capacity of the node
    GeneralNode(size_t index_, T value_, size_t capacity_) {
        value = value_;
        index = index_;
        capacity = capacity_;
        neighbors.reserve(capacity);
    }

    /// @brief Getter of the all node's neighbors
    /// @return const link to the node's neighbors vector
    const std::vector<std::pair<GeneralNode<T> *, size_t>> &getNeighbours() const noexcept { return neighbors; }

    /// @brief Getter of the node's value
    /// @return Value of the node
    T getValue() const noexcept { return value; }

    /// @brief Getter of the node's index
    /// @return Index of the node
    T getIndex() const noexcept { return index; }

    /// @brief Setter of the node's value
    /// @param value_ new value of the node
    void setValue(const T &value_) noexcept { value = value_; }

    /// @brief Add neighbour to the node
    /// @param neighbour new node's neighbour
    /// @param edgeIndex index of the edge between the node and its neighbour
    void addNeighbour(GeneralNode<T> *neighbour, size_t edgeIndex) noexcept {
        neighbors.emplace_back(neighbour, edgeIndex);
    }

    /// @brief Class destructor
    ~GeneralNode() = default;
}; // End of class 'GeneralNode'

template <typename T> class GeneralEdge {
  private:
    size_t start, end; // Edge's ends
    T weight;          // Edge's weight

  public:
    /// @brief Class default constructor
    GeneralEdge() { start = end = 0; }

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
    T getWeight() const noexcept { return weight; }

    /// @brief Getter of the edge's start node index
    /// @return Start node index of the edge
    size_t getStart() const noexcept { return start; }

    /// @brief Getter of the edge's end node index
    /// @return End node index of the edge
    size_t getEnd() const noexcept { return end; }

    /// @brief Setter of the edge's weight
    /// @param weight_ new weight of the edge
    void setWeight(T weight_) noexcept { weight = weight_; }

    /// @brief Class destructor
    ~GeneralEdge() = default;
}; // End of class 'GeneralEdge'

// GeneralGraph class
template <typename T, typename K> class GeneralGraph {
  private:
    std::vector<std::unique_ptr<GeneralEdge<T>>> edges; // All edges of the graph
    std::vector<std::unique_ptr<GeneralNode<K>>> nodes; // All nodes of the graph

  public:
    /// @brief Class constructor
    /// @param inputStream input stream with graph's data
    GeneralGraph(std::istream &inputStream = std::cin) {}

    /// @brief Class constructor
    /// @param filePath path to the file with graph data (text format)
    GeneralGraph(const std::string &filePath) {
        std::string line;
        std::ifstream stream(filePath);

        if (stream.is_open()) {
            int flag = 0;
            size_t n = 0;

            if (!(stream >> n) || !(stream >> flag)) {
                // TODO
            }

            K val;
            nodes.resize(n);
            try {
                for (size_t i = 0; i < n; i++) {
                    if (flag) {
                        stream >> val;
                        nodes[i] = std::make_unique<GeneralNode<K>>(i, val, 16);
                    } else {
                        nodes[i] = std::make_unique<GeneralNode<K>>(i, 16);
                    }
                }
                size_t in, out;
                T weight;
                while (stream >> in >> out >> weight) {
                    edges.emplace_back(std::make_unique<GeneralEdge<T>>(in, out, weight));
                    nodes[out]->addNeighbour(nodes[in].get(), edges.size() - 1);
                    nodes[in]->addNeighbour(nodes[out].get(), edges.size() - 1);
                }
            } catch (std::exception &e) {
                std::cout << e.what();
            }
        } else {
            std::cout << "Graph file is not found: " << filePath << ", aborting.." << std::endl;
        }
        stream.close();
    }

    /// @brief Getter of graph's edge by its index
    /// @param index index of the grap's edge
    /// @return Non-owning pointer to the edge in the graph
    const GeneralEdge<T> *getEdge(size_t index) const noexcept {
        if (index >= edges.size()) {
            return nullptr;
        }
        return edges[index].get();
    }

    /// @brief Getter of graph's node by its index
    /// @param index index of the grap's node
    /// @return Non-owning pointer to the node in the graph
    const GeneralNode<K> *getNode(size_t index) const noexcept {
        if (index >= nodes.size()) {
            return nullptr;
        }
        return nodes[index].get();
    }

    /// @brief Get graph's size
    /// @return size of the graph
    size_t getSize() const noexcept { return nodes.size(); }

    /// @brief Class destrutor
    ~GeneralGraph() = default;
}; // End of class 'GeneralGraph'

typedef GeneralGraph<int, int> Graph;

#endif // GRAPH_HPP
