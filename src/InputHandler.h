#pragma once

#include <SFML/Window/Keyboard.hpp>

class InputHandler
{
public:
    static bool isLeftPressed();
    static bool isRightPressed();
    static bool isJumpPressed();
    static bool isKeyPressed(sf::Keyboard::Key key);

private:
    InputHandler() = default;
    ~InputHandler() = default;
};
