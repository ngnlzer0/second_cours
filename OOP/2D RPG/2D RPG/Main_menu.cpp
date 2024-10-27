#include "Main_menu.h"

Main_menu::Main_menu(const sf::Vector2u& windowSize)
    : PlayButton(
        sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2.f - 250),
        sf::Vector2f(200, 200),
        "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/buttons/Buttons/Rect/PlayIcon/Default.png",
        "PLAY",
        "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/font/Gothical.ttf",
        sf::Vector2f(1.0f, 1.0f)),
    SettingButton(
        sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2.f),
        sf::Vector2f(200, 200),
        "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/buttons/Buttons/Square/Levels/Default.png",
        "SETTINGS",
        "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/font/Gothical.ttf",
        sf::Vector2f(1.0f, 1.0f)),
    ExitButton(
        sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2.f + 250),
        sf::Vector2f(200, 200),
        "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/buttons/Button/Rect/Default.png",
        "EXIT",
        "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/font/Gothical.ttf",
        sf::Vector2f(1.0f, 1.0f))
{
    if (!texture_back_fon.loadFromFile("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/background_2.png")) {
        throw std::runtime_error("Failed to load background texture");
    }
    Back_fon.setSize({ float(windowSize.x), float(windowSize.y) });
    Back_fon.setPosition({ 0, 0 });
    Back_fon.setTexture(&texture_back_fon);
}

void Main_menu::UpdateSelection(const sf::Vector2i& mousePos)
{
    // Скидання вибору для всіх кнопок
    ExitButton.Deselect(sf::Color(195, 200, 137));
    PlayButton.Deselect(sf::Color(195, 200, 137));
    SettingButton.Deselect(sf::Color(195, 200, 137));

    // Перевірка вибору
    if (ExitButton.GetGlobalBounds().contains(sf::Vector2f(mousePos)))
        ExitButton.Select(sf::Color(165, 170, 107));
    else if (PlayButton.GetGlobalBounds().contains(sf::Vector2f(mousePos)))
        PlayButton.Select(sf::Color(165, 170, 107));
    else if (SettingButton.GetGlobalBounds().contains(sf::Vector2f(mousePos)))
        SettingButton.Select(sf::Color(165, 170, 107));
}





