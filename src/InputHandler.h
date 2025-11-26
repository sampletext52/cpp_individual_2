#pragma once

#include <SFML/Window/Keyboard.hpp>

/**
 * @class InputHandler
 * @brief Централизованная система обработки ввода
 * 
 * Предоставляет статические методы для проверки состояния клавиатурного ввода.
 * Абстрагирует обработку ввода SFML и упрощает изменение привязок клавиш.
 */
class InputHandler
{
public:
    /**
     * @brief Проверяет, нажата ли в данный момент стрелка влево
     * @return True если стрелка влево нажата
     */
    static bool isLeftPressed();

    /**
     * @brief Проверяет, нажата ли в данный момент стрелка вправо
     * @return True если стрелка вправо нажата
     */
    static bool isRightPressed();

    /**
     * @brief Проверяет, нажата ли в данный момент клавиша пробел (прыжок)
     * @return True если клавиша пробел нажата
     */
    static bool isJumpPressed();

    /**
     * @brief Проверяет, нажата ли в данный момент определенная клавиша
     * @param key Клавиша для проверки
     * @return True если клавиша нажата
     */
    static bool isKeyPressed(sf::Keyboard::Key key);

private:
    InputHandler() = default; ///< Приватный конструктор (статический класс)
    ~InputHandler() = default; ///< Приватный деструктор (статический класс)
};
