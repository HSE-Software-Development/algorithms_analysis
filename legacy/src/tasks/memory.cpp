#include "memory.hpp"

// Redefinition of the allocating memory method
void *operator new(size_t size) {
    MemoryBenchmarking::getInstance().totalMemoryAllocated += size;
    return ::std::malloc(size);
}

// Redefinition of the deleting memory method
void operator delete(void *ptr) noexcept { ::std::free(ptr); }
