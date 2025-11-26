#include "Base.h"

Base::Base(float x, float y)
    : Entity(x, y, 60.f, 60.f)
    , m_health(MAX_HEALTH)
    , m_maxHealth(MAX_HEALTH)
{
    m_shape.setFillColor(sf::Color::Cyan);
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setOutlineThickness(2.f);
}

void Base::update(float deltaTime)
{
    if (m_health <= 0)
    {
        m_shape.setFillColor(sf::Color::Red);
    }
    else
    {
        float healthRatio = static_cast<float>(m_health) / static_cast<float>(m_maxHealth);
        unsigned char green = static_cast<unsigned char>(255 * healthRatio);
        m_shape.setFillColor(sf::Color(255 - green, green, 255));
    }
}

void Base::draw(sf::RenderWindow& window) const
{
    Entity::draw(window);
}

int Base::getHealth() const
{
    return m_health;
}

void Base::takeDamage(int damage)
{
    m_health -= damage;
    if (m_health < 0)
    {
        m_health = 0;
    }
}

bool Base::isDestroyed() const
{
    return m_health <= 0;
}

void Base::reset()
{
    m_health = MAX_HEALTH;
    m_shape.setFillColor(sf::Color::Cyan);
}
