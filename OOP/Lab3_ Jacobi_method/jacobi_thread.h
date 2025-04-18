#ifndef JACOBI_THREAD_HPP
#define JACOBI_THREAD_HPP

#include <vector>
#include <fstream>

std::vector<float> thread_jacobi(
    const std::vector<std::vector<float>>& A,
    const std::vector<float>& b,
    unsigned long max_iterations,
    float tolerance,
    unsigned long num_threads,
    std::ofstream& out);

#endif // JACOBI_THREAD_HPP
