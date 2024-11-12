#include "Game.h"

Game::Game()
    : window(windowSize, windowTitle), Main_Menu({ WIDHT_WINDOW, HIGHT_WINDOW }),
    tileMap(WIDHT_WINDOW / 32, HIGHT_WINDOW / 32), // Ініціалізація TileMap
    wfcMapGenerator(tileMap) // Генератор карти
{
	window_icon.loadFromFile("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/Icon_Games.png");
	window.setIcon(window_icon.getSize().x, window_icon.getSize().y, window_icon.getPixelsPtr());
	window.setPosition({ 0,0 });

	Mfont.loadFromFile("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/font/Gothical.ttf");

	head = new Armor(100,100);
	sword = new weapon(200, 200);
    stamina = new stamina_pot(300, 300);
    healt = new potion(400, 400);
}

void Game::HandleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

                // Перевірка на натиск кнопки Play
                if (Main_Menu.Get_PlayButton().GetGlobalBounds().contains(sf::Vector2f(mouse_pos))) {
                    Main_menu_open = false;
                    isGameActive = true; // Початок гри
                    wfcMapGenerator.generate(); // Генерація карти
                }
                // Перевірка на натиск кнопки Exit
                if (Main_Menu.Get_ExitButton().GetGlobalBounds().contains(sf::Vector2f(mouse_pos))) {
                    window.close();
                }
            }
            break;
        }
    }
}

void Game::Update(float delta_Time)
{
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

	Main_Menu.UpdateSelection(mouse_pos);
}

void Game::Render() {
    window.clear();

    // Малюємо фон меню, якщо меню відкрите
    if (Main_menu_open) {
        Main_Menu.draw(window, sf::RenderStates::Default);
    }
    // Якщо гра активна, малюємо карту
    if (isGameActive) {
        // Тут вам потрібно малювати вашу карту
        tileMap.draw(window); // Метод для малювання карти тайлів
    }

    // Малюємо кнопки предметів
    window.draw(head->Get_buttons());
    window.draw(sword->Get_Buttons());
    window.draw(stamina->Get_buttons());
    window.draw(healt->Get_Buttons());
    hero.Get_sprite()->draw(window);

    window.display();
}

void Game::Run()
{
	sf::Clock delta_time_clock;
	while(window.isOpen())
	{
		sf::Time delta_time = delta_time_clock.restart();
		HandleInput();
		Update(delta_time.asSeconds());
		Render();
	}
}
