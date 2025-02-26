#include"Game.h"
#include"Unit.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include"docktest/doctest.h"

int main()
{
    doctest::Context context;

    int res = context.run(); // Запускає тести

    if (context.shouldExit()) {
        return res; // Якщо були тільки тести, завершуємо програму
    }

     Game game;
     game.Run();

     return 0;
}