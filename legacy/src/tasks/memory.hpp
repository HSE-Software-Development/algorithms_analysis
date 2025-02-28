#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <iostream>
#include <memory>

// Memory benchmarking global class
class MemoryBenchmarking {
  private:
    size_t totalMemoryAllocated; // Total bytes of allocated memory

    /// @brief Class default constructor
    explicit MemoryBenchmarking() = default;

    MemoryBenchmarking(MemoryBenchmarking const &) = delete;
    MemoryBenchmarking &operator=(MemoryBenchmarking const &) = delete;

    /// @brief Class default destructor
    ~MemoryBenchmarking() = default;

  public:
    /// @brief Getter of instance of memory benchmarking class
    /// @return static link to the instance of this class
    static MemoryBenchmarking &getInstance() {
        static MemoryBenchmarking memoryBenchmarkingInstance;

        return memoryBenchmarkingInstance;
    }

    /// @brief Getter of the total number of allocated bytes value
    /// @return total number of allocated bytes value
    size_t getTotalMemoryAllocated() const noexcept { return totalMemoryAllocated; }

    // Friends methods of this class
    friend void *operator new(size_t size);
    friend void operator delete(void *ptr) noexcept;
};

// Redefinition of the allocating memory method
void *operator new(size_t size);

// Redefinition of the deleting memory method
void operator delete(void *ptr) noexcept;

#endif // MEMORY_HPP