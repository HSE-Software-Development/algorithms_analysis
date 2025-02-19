#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <iostream>
#include <memory>

class MemoryBenchmarking {
  private:
    size_t totalMemoryAllocated;

    explicit MemoryBenchmarking() = default;

    MemoryBenchmarking(MemoryBenchmarking const &) = delete;
    MemoryBenchmarking &operator=(MemoryBenchmarking const &) = delete;

    ~MemoryBenchmarking() = default;

  public:
    static MemoryBenchmarking &getInstance() {
        static MemoryBenchmarking memoryBenchmarkingInstance;

        return memoryBenchmarkingInstance;
    }

    size_t getTotalMemoryAllocated() const noexcept { return totalMemoryAllocated; }

    friend void *operator new(size_t size);
    friend void operator delete(void *ptr) noexcept;
};

void *operator new(size_t size);

void operator delete(void *ptr) noexcept;

#endif // MEMORY_HPP