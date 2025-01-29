#ifndef TASKS_HPP
#define TASKS_HPP

#include <functional>

#include "../algorithms/algorithms.hpp"

// Task class
class Task {
  public:
    /// @brief Run task method
    virtual void run(int logLevel) = 0;

    /// @brief Class destructor
    virtual ~Task() = default;
}; // End of class 'Task'

// SSSP task class
template <typename T, typename K> class SSSP : public Task {
  private:
    std::vector<std::unique_ptr<GeneralGraph<T, K>>>
        graphs; // Non-owning pointer to the graph  for the task
    std::vector<size_t> startNodeIndexes; // Start node index for the task
    std::vector<std::vector<T>>
        distances; // Distances from the start node to all others
    std::function<void(size_t, GeneralGraph<T, size_t> *, std::vector<T> &)>
        algorithm; // Algorithm for the task

  public:
    /// @brief Class constructor
    /// @param filePath path to the file with graph data (if it is empty
    /// std::cin will be used
    /// @param startNodeIndex_ start node index in the graph
    /// @param algorithm algorithm function instance
    SSSP(std::vector<std::string> filePaths,
         std::vector<size_t> startNodeIndexes_,
         const std::function<void(size_t, GeneralGraph<T, size_t> *,
                                  std::vector<T> &)> &algorithm_) {
        bool is_ok = !filePaths.empty() && !startNodeIndexes_.empty() &&
                     filePaths.size() == startNodeIndexes_.size();
        if (is_ok) {
            algorithm = algorithm_;
            auto size = filePaths.size();

            for (size_t index = 0; index < size; index++) {
                auto filePath = filePaths[index];
                auto startNodeIndex = startNodeIndexes_[index];

                if (filePath.empty()) {
                    graphs.emplace_back(
                        std::make_unique<GeneralGraph<T, K>>(std::cin));
                    std::cin >> startNodeIndex;
                } else {
                    graphs.emplace_back(
                        std::make_unique<GeneralGraph<T, K>>(filePath));
                }
                startNodeIndexes.emplace_back(startNodeIndex);
            }
        }
    }

    /// @brief Executor of the task
    void run(int logLevel) override {
        std::cout << "abc" << std::endl;
        algorithm(startNodeIndexes[0], graphs[0].get(), distances[0]);
        std::cout << distances[0][0] << std::endl;
        // switch (log)
    }

    /// @brief Class destructor
    ~SSSP() = default;
}; // End of class 'SSSP'

// APSP task class
template <typename T, typename K> class APSP : public Task {
  private:
    std::vector<GeneralGraph<T, K> *>
        graphs; // Non-owning pointer to the graph for the task
    std::vector<std::vector<std::vector<T>>>
        distances; // Distances from any node to any others
    std::function<void(const GeneralGraph<T, size_t> *, std::vector<std::vector<T>> &)>
        algorithm; // Algorithm for the task

  public:
    /// @brief Class constructor
    /// @param filePath path to the file with graph data (if it is empty
    /// std::cin will be used)
    /// @param algorithm algorithm function instance
    APSP(std::vector<std::string> filePaths,
         std::function<void(const GeneralGraph<T, size_t> *,
                            std::vector<std::vector<T>> &)>
             algorithm_) {
        bool is_ok = !filePaths.empty();
        if (is_ok) {
            algorithm = algorithm_;
            auto size = filePaths.size();

            for (size_t index = 0; index < size; index++) {
                auto filePath = filePaths[index];

                if (filePath.empty()) {
                    graphs.emplace_back(
                        std::make_unique<GeneralGraph<T, K>>(std::cin));
                } else {
                    graphs.emplace_back(
                        std::make_unique<GeneralGraph<T, K>>(filePath));
                }
            }
        }
    }

    /// @brief Executor of the task
    void run(int logLeve) override {}

    /// @brief Class destructor
    ~APSP() = default;
};

#endif // TASKS_HPP
