#define PICOBENCH_IMPLEMENT_WITH_MAIN
#include "picobench.hpp"

#include <vector>
#include <cstdlib> // for rand

// Benchmarking function written by the user:
static void rand_vector(picobench::state& s)
{
    std::vector<int> v;
    for (auto _ : s)
    {
        v.push_back(rand());
    }
}
PICOBENCH(rand_vector); // Register the above function with picobench

// Another benchmarking function:
static void rand_vector_reserve(picobench::state& s)
{
    std::vector<int> v;
    v.reserve(s.iterations());
    for (auto _ : s)
    {
        v.push_back(rand());
    }
}
PICOBENCH(rand_vector_reserve);
