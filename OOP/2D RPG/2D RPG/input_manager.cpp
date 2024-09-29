#include "input_manager.h"

input_manager::input_manager()
{
}

input_manager::~input_manager()
{
}

sf::Keyboard::Key input_manager::KeyboardConfiguration(Input key)
{
    if (key == Left) return sf::Keyboard::A;
    if (key == Right) return sf::Keyboard::D;
    if (key == Up) return sf::Keyboard::W;
    if (key == Down) return sf::Keyboard::S;
    if (key == LoadMap) return sf::Keyboard::L;

    return sf::Keyboard::Unknown;
}

    bool input_manager::IsKeyBoardPressed(sf::Keyboard::Key key) {
        return sf::Keyboard::isKeyPressed(key);
    }

    bool input_manager::IsPressed(Input key, unsigned int joystick) {
        sf::Keyboard::Key myKeyboardKey = KeyboardConfiguration(key);
        if (myKeyboardKey != sf::Keyboard::Unknown) {
            if (IsKeyBoardPressed(myKeyboardKey)) {
                return true;
            }
        }

        return false;
   }

