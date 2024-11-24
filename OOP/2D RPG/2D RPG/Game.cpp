#include "Game.h"

Game::Game()
    : window(windowSize, windowTitle), Main_Menu({ WIDHT_WINDOW, HIGHT_WINDOW }),
    inventory(9, 50.0, "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/buttons/Button/Rect/Default.png") // Ініціалізація інвентаря
{
    window_icon.loadFromFile("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/Icon_Games.png");
    window.setIcon(window_icon.getSize().x, window_icon.getSize().y, window_icon.getPixelsPtr());
    window.setPosition({ 0, 0 });

    Mfont.loadFromFile("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/font/Gothical.ttf");

    head = new Armor(100, 100);
    sword = new weapon(200, 200);
    stamina = new stamina_pot(300, 300);
    healt = new potion(400, 400);

    // Додаємо предмети до інвентаря
    inventory.addItem(std::make_shared<Armor>(*head));
    inventory.addItem(std::make_shared<weapon>(*sword));
    inventory.addItem(std::make_shared<stamina_pot>(*stamina));
    inventory.addItem(std::make_shared<potion>(*healt));

    hero.Set_new_HP(60);
    hero.Set_new_stamina(30);
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

                if (Main_Menu.Get_PlayButton().GetGlobalBounds().contains(sf::Vector2f(mouse_pos))) {
                    main_menu_open = false;
                    isGameActive = true;
                }
                else if (Main_Menu.Get_ExitButton().GetGlobalBounds().contains(sf::Vector2f(mouse_pos))) {
                    window.close();
                }
                inventory.handleInput(event, window);
            }
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::I) { // Відкрити/закрити інвентар
                isGameActive = !isGameActive; // Тогл режиму
            }
            else {
                // Обробка подій героя
                hero.handleInput(event, window);
            }
            break;

        case sf::Event::KeyReleased:
            // Обробка зупинки дій героя
            hero.handleInput(event, window);
            break;

        default:
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
        inventory.update(window);
        hero.processMovement(deltaTime, window);
        hero.update(deltaTime);
        hero.updateBars();
    }
}

void Game::Render() {
    window.clear();

    if (main_menu_open) {
        Main_Menu.draw(window, sf::RenderStates::Default);
    }
    else if (isGameActive) {
        // Малювання ігрових елементів
         
        // Малювання інвентаря
        inventory.draw(window);
        // tileMap.draw(window); // Якщо використовується карта
        hero.drawBars(window);
        hero.Get_sprite()->draw(window);

    }

    window.display();
}


void Game::Run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        HandleInput();
        Update(deltaTime);
        Render();
    }
}

