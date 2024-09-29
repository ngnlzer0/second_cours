#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>


class input_manager
{
public:
    input_manager();
    ~input_manager();

    enum Input
    {
        Left = 0,
        Right,
        Up,
        Down,
        LoadMap,

        KeyCount      ///< Keep last -- the total number of inputs
    };

    sf::Keyboard::Key KeyboardConfiguration(Input key);
    bool IsKeyBoardPressed(sf::Keyboard::Key);
    bool IsPressed(Input key, unsigned int joystick = 0);
};

