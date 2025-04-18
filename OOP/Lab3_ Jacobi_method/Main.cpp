#include <doctest.h>
#include <iostream>
#include <vector>
#include "single_threaded_Jacobi_method.h"
#include "Timer.h"
#include "multithreading_Jacobi_methods.h"

int main() {
    doctest::Context context;
    int res = context.run(); // запускає тести

    if (context.shouldExit()) {
        return res; // вихід, якщо тести мають завершити програму
    }

    // Далі йде код для Jacobi

    /*
    std::vector<std::vector<double>> A = {
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

    std::vector<double> B = { 3,5,21,8,3,15,45,12,7,91,11,24,54,11,15 };

*/


    int size = 64;

    std::vector<std::vector<double>> A(size, std::vector<double>(size));
    std::vector<double> B(size);

    // Генеруй діагонально домінантну матрицю:
    for (int i = 0; i < size; ++i) {
        double sum = 0;
        for (int j = 0; j < size; ++j) {
            A[i][j] = (i == j) ? 0 : (rand() % 5);
            sum += std::abs(A[i][j]);
        }
        A[i][i] = sum + rand() % 5 + 1;
        B[i] = rand() % 100;
    }


    single_threaded_Jacobi_method solver(A, B, size);
    double E = 0.000005;

    Timer timer;
    timer.start();
    solver.Main_method(E);
    //solver.ShowX();


    auto ms = timer.stop();
    std::cout << "Program time = " << ms.count() << " ms - one thread" <<  std::endl;

    jacobi_threaded tht(A, B, size, 2);

    Timer clocktht;

    clocktht.start();
    tht.Main_method(E);
    //tht.ShowX();

    auto mstht = clocktht.stop();
    std::cout << "Program time = " << mstht.count() << " ms - multitherad" << std::endl;

    return 0;
}

