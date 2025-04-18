#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include"Timer.h"
#include "single_threaded_Jacobi_method.h"


TEST_CASE("Check to work single_thread_Jacobi_method")
{
    std::vector<std::vector<double>> A =
    { {8,4,2},
        {3,9,0},
        {6,2,12}
    };
    std::vector<double> B = { 16,12,8 };

    single_threaded_Jacobi_method test(A, B, 3);

    Timer clock{};

    clock.start();

    double E = 0.0005;
    test.Main_method(E);


    auto ms = clock.stop();
    std::cout << "Program time = " << ms.count() << " ms" << std::endl;
    
    CHECK(test.Get_Xi(0) >= 1.692 - E*2);
    CHECK(test.Get_Xi(0) <= 1.692 + E*2);

    CHECK(test.Get_Xi(1) >= 0.769 - E*2);
    CHECK(test.Get_Xi(1) <= 0.769 + E*2);

    CHECK(test.Get_Xi(2) >= -0.307 - E*2);
    CHECK(test.Get_Xi(2) <= -0.307 + E*2);
    
}