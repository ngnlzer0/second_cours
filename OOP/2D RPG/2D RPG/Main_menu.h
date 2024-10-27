#pragma once

#include "Includer.h"
#include "Buttons.h"

class Main_menu {
private:
    sf::RectangleShape Back_fon;
    sf::Texture texture_back_fon;

    Buttons PlayButton;     // Звичайні об'єкти
    Buttons SettingButton;  // Звичайні об'єкти
    Buttons ExitButton;     // Звичайні об'єкти

public:
    Main_menu(const sf::Vector2u& windowSize);
    Main_menu() = default;

    void UpdateSelection(const sf::Vector2i& mousePos);

    Buttons& Get_PlayButton() { return PlayButton; }
    Buttons& Get_SettingButton() { return SettingButton; }
    Buttons& Get_ExitButton() { return ExitButton; }

    // Метод draw
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // Малюємо фон та кнопки
        target.draw(Back_fon, states);
        PlayButton.draw(target, states);        // Використання методу draw кнопки
        SettingButton.draw(target, states);
        ExitButton.draw(target, states);
    }
};



