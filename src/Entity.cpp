#include "Entity.h"

Entity::Entity(float x, float y, float width, float height)
    : m_alive(true)
{
    m_shape.setSize(sf::Vector2f(width, height));
    m_shape.setPosition(sf::Vector2f(x, y));
}

void Entity::draw(sf::RenderWindow& window) const
{
    if (m_alive)
    {
        window.draw(m_shape);
    }
}

sf::Vector2f Entity::getPosition() const
{
    return m_shape.getPosition();
}

sf::FloatRect Entity::getBounds() const
{
    return m_shape.getGlobalBounds();
}

void Entity::setPosition(float x, float y)
{
    m_shape.setPosition(sf::Vector2f(x, y));
}

bool Entity::isAlive() const
{
    return m_alive;
}

void Entity::setAlive(bool alive)
{
    m_alive = alive;
}

