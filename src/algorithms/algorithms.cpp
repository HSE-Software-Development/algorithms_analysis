#include "algorithms.hpp"

/// @brief Get current time in ms
/// @return current time in ms
uint64_t getTimeInMs() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}