#include "Bullet.h"
#include <cmath>

Bullet::Bullet(float x, float y, float targetX, float targetY, float speed)
    : Entity(x, y, 8.f, 8.f)
    , m_target(targetX, targetY)
    , m_speed(speed)
{
    m_shape.setFillColor(sf::Color::White);
    
    // Вычисляем направление
    sf::Vector2f direction = m_target - sf::Vector2f(x, y);
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    
    if (distance > 0.1f)
    {
        direction /= distance;
        m_velocity = direction * m_speed;
    }
    else
    {
        m_velocity = sf::Vector2f(0.f, 0.f);
    }
}

void Bullet::update(float deltaTime)
{
    if (!m_alive)
        return;

    sf::Vector2f currentPos = m_shape.getPosition();
    sf::Vector2f movement = m_velocity * deltaTime;
    m_shape.move(movement);
    
    // Проверяем, достигли ли цели
    currentPos = m_shape.getPosition();
    float distance = std::sqrt(
        (m_target.x - currentPos.x) * (m_target.x - currentPos.x) +
        (m_target.y - currentPos.y) * (m_target.y - currentPos.y)
    );
    
    if (distance < TARGET_THRESHOLD || hasReachedTarget())
    {
        m_alive = false;
    }
}

void Bullet::draw(sf::RenderWindow& window) const
{
    Entity::draw(window);
}

int Bullet::getDamage() const
{
    return DAMAGE;
}

bool Bullet::hasReachedTarget() const
{
    sf::Vector2f currentPos = m_shape.getPosition();
    float distance = std::sqrt(
        (m_target.x - currentPos.x) * (m_target.x - currentPos.x) +
        (m_target.y - currentPos.y) * (m_target.y - currentPos.y)
    );
    return distance < TARGET_THRESHOLD;
}

