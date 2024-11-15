#include "Game.h"

Game::Game()
    : window(windowSize, windowTitle), Main_Menu({ WIDHT_WINDOW, HIGHT_WINDOW })
    //tileMap(WIDHT_WINDOW / 16, HIGHT_WINDOW / 16), // Ініціалізація TileMap
    //wfcMapGenerator(tileMap) // Генератор карти
{
	window_icon.loadFromFile("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/Icon_Games.png");
	window.setIcon(window_icon.getSize().x, window_icon.getSize().y, window_icon.getPixelsPtr());
	window.setPosition({ 0,0 });

	Mfont.loadFromFile("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/font/Gothical.ttf");

    //wfcMapGenerator.generate();

	head = new Armor(100,100);
	sword = new weapon(200, 200);
    stamina = new stamina_pot(300, 300);
    healt = new potion(400, 400);
}

void Game::HandleInput()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

                if (Main_Menu.Get_PlayButton().GetGlobalBounds().contains(sf::Vector2f(mouse_pos))) {
                    main_menu_open = false;
                    isGameActive = true;
                }
                else if (Main_Menu.Get_ExitButton().GetGlobalBounds().contains(sf::Vector2f(mouse_pos))) {
                    window.close();
                }
            }
            break;

        default:
            hero.handleInput(event);
            break;
        }
    }
}

void Game::Update(float deltaTime)
{
    if (main_menu_open) {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        Main_Menu.UpdateSelection(mouse_pos);
    }

    if (isGameActive) {
        hero.processMovement(deltaTime);
        hero.update(deltaTime);
    }
}

void Game::Render()
{
    window.clear();

    if (main_menu_open) {
        Main_Menu.draw(window, sf::RenderStates::Default);
    }
    else if (isGameActive) {
        //tileMap.draw(window);
        hero.Get_sprite()->draw(window);
    }

    window.display();
}

void Game::Run()
{
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        HandleInput();
        Update(deltaTime);
        Render();
    }
}
