#pragma once
#include <list>
#include "Main_menu.h"
#include "Includer.h"
#include "Unit.h"
#include "Inventors.h"
#include "potion.h"
#include "stamina_pot.h"
#include "Hero.h"

class Game {
private:
    sf::Image window_icon;
    sf::VideoMode windowSize = { WIDHT_WINDOW, HIGHT_WINDOW };
    sf::String windowTitle = "2D RPG game";

    sf::RenderWindow window;
    Main_menu Main_Menu;



    bool main_menu_open = true;
    bool isGameActive = false;

    sf::Font Mfont;

    Armor* head;
    weapon* sword;
    stamina_pot* stamina;
    potion* healt;

    Hero hero = Hero();
    Inventors inventory; // Інвентар гравця

    void HandleInput();
    void Update(float delta_Time);
    void Render();

public:
    Game();

    void Run();
};


