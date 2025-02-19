#include "memory.hpp"

void *operator new(size_t size) {
    MemoryBenchmarking::getInstance().totalMemoryAllocated += size;
    return ::std::malloc(size);
}

void operator delete(void *ptr) noexcept { ::std::free(ptr); }
