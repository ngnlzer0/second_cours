// barrier.hpp
#pragma once
#include <atomic>

class spinning_barrier {
    std::atomic<unsigned int> count;
    std::atomic<unsigned int> generation;
    const unsigned int num_threads;

public:
    explicit spinning_barrier(unsigned int count_)
        : count(count_), generation(0), num_threads(count_) {
    }

    void wait() {
        unsigned int gen = generation.load();
        if (count.fetch_sub(1) == 1) {
            count.store(num_threads);
            generation.fetch_add(1);
        }
        else {
            while (generation.load() == gen) {
                std::this_thread::yield();
            }
        }
    }
};
