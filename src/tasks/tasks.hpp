#ifndef TASKS_HPP
#define TASKS_HPP

#include <functional>

#include "../algorithms/algorithms.hpp"

// Task class
class Task {
  public:
    /// @brief Run task method
    virtual void run(int logLevel) = 0;

    /// @brief Get current time in ms
    /// @return current time in ms
    uint64_t getTimeInMs() {
        using namespace std::chrono;
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }

    /// @brief Class destructor
    virtual ~Task() = default;

}; // End of class 'Task'

// SSSP task class
template <typename T, typename K> class SSSP : public Task {
  private:
    std::vector<size_t> startNodeIndexes;     // Start node index for the task
    std::vector<GeneralGraph<T, K> *> graphs; // Non-owning pointer to the graphs for the task
    std::function<void(size_t, GeneralGraph<T, K> *, std::vector<T> &)> algorithm; // Algorithm for the task
    std::vector<std::vector<T>> distances; // Distances from the start node to all others
    std::vector<double> benchmarks;        // Algorithm executions time in seconds

  public:
    /// @brief Class constructor
    /// @param graphs_ vector of all graphs for the task
    /// @param startNodeIndexes_ vector of all start nodes for the task
    /// @param algorithm_ algorithm to complete the task
    SSSP(const std::vector<GeneralGraph<T, K> *> &graphs_, const std::vector<size_t> &startNodeIndexes_,
         const std::function<void(size_t, GeneralGraph<T, K> *, std::vector<T> &)> &algorithm_) {
        bool is_ok = !graphs_.empty() && !startNodeIndexes_.empty() && graphs_.size() == startNodeIndexes_.size();

        if (is_ok) {
            const auto size = graphs_.size();

            startNodeIndexes = startNodeIndexes_;
            distances.resize(size);
            benchmarks.resize(size);
            graphs = graphs_;
            algorithm = algorithm_;
        } else {
            std::cout << "The number of graphs is 0 or is not equal to the number of start nodes, aborting.."
                      << std::endl;
        }
    }

    /// @brief Getter of SSSP start node's indexes
    /// @return All start node's indexes vector
    const std::vector<size_t> &getStartNodeIndexes() const { return startNodeIndexes; }

    /// @brief Getter of SSSP distances
    /// @return All distances vector
    const std::vector<std::vector<T>> &getDistances() const { return distances; }

    /// @brief Getter of SSSP graphs
    /// @return All graphs vector
    const std::vector<GeneralGraph<T, K> *> &getGraphs() const { return graphs; }

    /// @brief Executor of the task
    /// @param logLevel logging level
    void run(int logLevel = 1) override {
        // TODO
        const auto size = graphs.size();

        for (size_t i = 0; i < size; i++) {
            std::cout << "SSSP for graph #" << i + 1 << ":\n";
            benchmarks[i] = static_cast<double>(getTimeInMs());
            algorithm(startNodeIndexes[i], graphs[i], distances[i]);
            benchmarks[i] = (static_cast<double>(getTimeInMs()) - benchmarks[i]);
            for (size_t j = 0; j < graphs[i]->getSize(); j++) {
                std::cout << "\t" << j + 1 << ") Distanse from node #" << startNodeIndexes[i] << " to node #" << j
                          << " = " << distances[i][j] << "; "
                          << "time = " << benchmarks[i] << " sec\n";
            }
            std::cout << std::endl;
        }
    }

    /// @brief Class destructor
    ~SSSP() = default;
}; // End of class 'SSSP'

// APSP task class
template <typename T, typename K> class APSP : public Task {
  private:
    std::vector<GeneralGraph<T, K> *> graphs;           // Non-owning pointer to the graphs for the task
    std::vector<std::vector<std::vector<T>>> distances; // Distances from any node to any others
    std::function<void(const GeneralGraph<T, K> *,
                       std::vector<std::vector<T>> &)> algorithm; // Algorithm for the task

  public:
    /// @brief Class constructor
    /// @param graphs_ vector of all graphs for the task
    /// @param algorithm algorithm function instance
    APSP(const std::vector<GeneralGraph<T, K> *> &graphs_,
         std::function<void(const GeneralGraph<T, K> *, std::vector<std::vector<T>> &)> algorithm_) {
        bool is_ok = !graphs_.empty();

        if (is_ok) {
            const auto size = graphs_.size();

            distances.resize(size);
            graphs = graphs_;
            algorithm = algorithm_;
        } else {
            std::cout << "The number of graphs is 0, aborting.." << std::endl;
        }
    }

    /// @brief Executor of the task
    void run(int logLevel = 1) override {}

    /// @brief Class destructor
    ~APSP() = default;
};

#endif // TASKS_HPP
