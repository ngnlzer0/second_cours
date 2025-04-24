#include "doctest.h"
#include "single_threaded_Jacobi_method.h"
#include "thread_jacobi.h"
#include "Timer.h"
#include "utils.hpp"
#include <omp.h>
#include <thread>

using namespace std;

int main() {
    doctest::Context context;
    int res = context.run(); // запускає тести

    if (context.shouldExit()) {
        return res; // вихід, якщо тести мають завершити програму
    }


    
    std::vector<std::vector<double>> A_15 = {
    {55, 4, 3, 2, 5, 3, 2, 1, 4, 2, 1, 2, 1, 3, 1},
    {3, 60, 4, 3, 2, 4, 3, 2, 1, 3, 2, 2, 2, 1, 2},
    {4, 2, 50, 2, 1, 3, 2, 2, 3, 4, 2, 1, 2, 3, 1},
    {2, 3, 2, 58, 3, 2, 4, 3, 2, 1, 3, 2, 2, 1, 3},
    {3, 4, 1, 2, 56, 4, 3, 2, 1, 3, 2, 1, 3, 4, 2},
    {2, 2, 3, 4, 2, 52, 4, 3, 2, 1, 2, 3, 2, 2, 1},
    {1, 3, 2, 3, 4, 3, 53, 2, 1, 3, 3, 1, 2, 2, 2},
    {3, 2, 1, 3, 2, 1, 4, 57, 3, 2, 1, 3, 2, 1, 3},
    {2, 1, 3, 2, 1, 2, 1, 2, 54, 3, 2, 2, 1, 2, 1},
    {2, 3, 2, 1, 3, 2, 3, 1, 2, 59, 1, 2, 2, 3, 2},
    {1, 2, 1, 3, 2, 3, 2, 2, 3, 1, 51, 3, 2, 2, 3},
    {2, 2, 1, 2, 3, 1, 2, 2, 2, 2, 3, 50, 3, 2, 1},
    {3, 1, 2, 2, 1, 2, 1, 3, 2, 3, 2, 3, 56, 1, 2},
    {1, 2, 3, 1, 2, 3, 2, 1, 3, 2, 1, 2, 2, 53, 1},
    {2, 2, 1, 3, 1, 1, 3, 2, 1, 2, 3, 1, 2, 3, 55}
    };

    std::vector<double> B_15 = { 3,5,21,8,3,15,45,12,7,91,11,24,54,11,15 };
    int size_15 = 15;


    single_threaded_Jacobi_method solver_15(A_15, B_15, size_15);
    double E = 0.000005;

    std::cout << "Check out for matrix 15x15 : " << std::endl;

    Timer timer_15;
    timer_15.start();
    solver_15.Main_method(E);

    auto ms_15 = timer_15.stop();

    solver_15.ShowX();

    std::cout << "Program time = " << ms_15.count() << " ms - one thread" <<  std::endl;


    thread_jacobi s_15(A_15, B_15);

    Timer t_15;
    t_15.start();
    s_15.jacobi_method(E);

    auto m_15 = t_15.stop();

    print_solution(s_15.Get_x());

    std::cout << "Program time = " << m_15.count() << " ms - multi thread" << std::endl;

    std::cout << "Part 2 //////////////////////////////////////////////////////////////////////////////////" << std::endl;

    std::cout << "Check out for matrix 10k x 10k : " << std::endl;
    ulong size = 10000;
    double tolerance = 0.0005; //if tolerance =< 0.00001, multythread method work very slow
    ulong workers = 8;

    std::vector<std::vector<double>> A;
    std::vector<double> b;

    // Generate the diagonally dominant matrix and vector
    generate_diagonal_dominant_matrix(size, A, 1.0, 10.0);
    generate_vector(size, b, 1.0, 10.0);

    single_threaded_Jacobi_method solver(A, b, size);

    Timer timer;
    timer.start();
    solver.Main_method(tolerance);

    microseconds ms = timer.stop();

    //solver.ShowX();

    std::cout << "Program time = " << ms.count() / 1'000'000.0 << " sec - one thread" << std::endl;

    thread_jacobi t_j(A, b);
    Timer clock;
    clock.start();

    t_j.jacobi_method(tolerance);

    microseconds ms1 = clock.stop();

    //print_solution(t_j.Get_x());
    std::cout << "Program time = " << ms1.count() / 1'000'000.0 << " sec - multi thread" << std::endl;


    return 0;
}

