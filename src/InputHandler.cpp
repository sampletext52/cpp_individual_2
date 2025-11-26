#include "InputHandler.h"

bool InputHandler::isLeftPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
}

bool InputHandler::isRightPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
}

bool InputHandler::isJumpPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
}

bool InputHandler::isKeyPressed(sf::Keyboard::Key key)
{
    return sf::Keyboard::isKeyPressed(key);
}
