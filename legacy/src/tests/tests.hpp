#ifndef TESTS_HPP
#define TESTS_HPP

#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "../tasks/tasks.hpp"

template <typename T, typename K> struct FunctionType {
    typedef std::function<void(size_t, GeneralGraph<T, K> *, std::vector<T> &)> Type;
};

#endif // TESTS_HPP