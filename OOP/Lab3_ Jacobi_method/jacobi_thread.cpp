#include "jacobi_thread.hpp"
#include <thread>
#include <atomic>
#include <cmath>
#include <vector>

#include "utils.hpp"         // для print_metrics, write_csv
#include "barrier.hpp"       // spinning_barrier

using namespace std;

namespace {
    vector<std::vector<float>> A;
    std::vector<float> b;
    std::atomic<float> global_error;
    std::atomic<bool> stop;
    unsigned long iterations;
    float tolerance;
    unsigned long n;

    struct Job {
        unsigned long start;
        unsigned long end;
        Job(unsigned long s, unsigned long e) : start(s), end(e) {}
    };

    std::vector<Job> jobs;

    void split_jobs(unsigned long total_rows, unsigned long num_threads) {
        jobs.clear();
        unsigned long chunk = total_rows / num_threads;
        unsigned long rest = total_rows % num_threads;
        unsigned long start = 0;

        for (unsigned long i = 0; i < num_threads; ++i) {
            unsigned long end = start + chunk + (rest-- > 0 ? 1 : 0);
            jobs.emplace_back(start, end);
            start = end;
        }
    }

    void worker(
        unsigned long id,
        std::vector<float>& curr,
        std::vector<float>& prev,
        spinning_barrier& barrier,
        std::atomic<unsigned long>& curr_iteration)
    {
        for (unsigned long iter = 0; iter < iterations; ++iter) {
            global_error.store(0.0f);

            barrier.wait();  // sync before work

            for (unsigned long i = jobs[id].start; i < jobs[id].end; ++i) {
                float sigma = 0.0f;
                for (unsigned long j = 0; j < n; ++j) {
                    if (j != i) sigma += A[i][j] * prev[j];
                }
                curr[i] = (b[i] - sigma) / A[i][i];
            }

            barrier.wait(); // sync before error calculation

            float local_error = 0.0f;
            for (unsigned long i = jobs[id].start; i < jobs[id].end; ++i) {
                local_error += std::abs(curr[i] - prev[i]);
            }
            global_error.fetch_add(local_error, std::memory_order_relaxed);

            barrier.wait(); // sync before checking convergence

            if (id == 0) {
                global_error = global_error / n;
                if (global_error <= tolerance) {
                    stop = true;
                }
                else {
                    std::swap(curr, prev);
                }
                curr_iteration = iter + 1;
            }

            barrier.wait(); // sync after convergence check
            if (stop) break;
        }
    }
}

std::vector<float> thread_jacobi(
    const std::vector<std::vector<float>>& _A,
    const std::vector<float>& _b,
    unsigned long max_iterations,
    float _tolerance,
    unsigned long num_threads,
    std::ofstream& out)
{

    A = _A;
    b = _b;
    n = b.size();
    iterations = max_iterations;
    tolerance = _tolerance;
    stop = false;
    global_error = 0.0f;

    std::vector<float> x_curr(n, 0.0f);
    std::vector<float> x_prev(n, 0.0f);

    split_jobs(n, num_threads);
    spinning_barrier barrier(num_threads);
    std::vector<std::thread> threads;
    std::atomic<unsigned long> curr_iteration(0);

    for (unsigned long i = 0; i < num_threads; ++i) {
        threads.emplace_back(worker, i, std::ref(x_curr), std::ref(x_prev), std::ref(barrier), std::ref(curr_iteration));
    }

    for (auto& t : threads) t.join();


    return x_curr;
}

