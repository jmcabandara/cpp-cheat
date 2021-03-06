#include "common.hpp"

int main(int argc, char **argv) {
    typedef uint64_t I;
    std::vector<I> randoms;
    size_t i, j, n, granule, base;
    std::priority_queue<I> heap;
    std::set<I> bst;
    unsigned int seed = std::random_device()();

    // CLI arguments.
    if (argc > 1) {
        n = std::stoi(argv[1]);
    } else {
        n = 10000000;
    }
    if (argc > 2) {
        granule = std::stoi(argv[2]);
    } else {
        granule = 10000;
    }

    // Action.
    for (i = 0; i < n; ++i) {
        randoms.push_back(i);
    }
    std::shuffle(randoms.begin(), randoms.end(), std::mt19937(seed));
    for (i = 0; i < n / granule; ++i) {
        using clk = std::chrono::high_resolution_clock;
        decltype(clk::now()) start, end;
        base = i * granule;

        // Heap.
        start = clk::now();
        for (j = 0; j < granule; ++j) {
            heap.emplace(randoms[base + j]);
        }
        end = clk::now();
        auto dt_heap = (end - start) / granule;

        // BST.
        start = clk::now();
        for (j = 0; j < granule; ++j) {
            bst.insert(randoms[base + j]);
        }
        end = clk::now();
        auto dt_bst = (end - start) / granule;

        // Output.
        std::cout
            << base << " "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(dt_heap).count() << " "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(dt_bst).count() << std::endl;
    }

    // Sanity check.
    for (auto it = bst.rbegin(); it != bst.rend(); ++it) {
        assert(*it == heap.top());
        heap.pop();
    }
}
