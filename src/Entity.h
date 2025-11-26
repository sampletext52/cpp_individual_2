#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

/**
 * @class Entity
 * @brief Базовый класс для всех игровых сущностей
 * 
 * Предоставляет общий интерфейс для всех объектов в игре.
 * Использует паттерн полиморфизма для расширяемости.
 */
class Entity
{
public:
    Entity(float x, float y, float width, float height);
    virtual ~Entity() = default;

    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) const;
    
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    void setPosition(float x, float y);
    bool isAlive() const;
    void setAlive(bool alive);

protected:
    sf::RectangleShape m_shape;
    bool m_alive;
};

