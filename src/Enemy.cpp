#include "Enemy.h"
#include "Base.h"
#include <cmath>

Enemy::Enemy(float x, float y, Type type)
    : Entity(x, y, 30.f, 30.f)
    , m_type(type)
    , m_target(nullptr)
    , m_speed(50.f)
    , m_damage(10)
    , m_reward(10)
{
    initializeByType();
}

void Enemy::initializeByType()
{
    switch (m_type)
    {
    case Type::Basic:
        m_speed = 50.f;
        m_damage = 10;
        m_reward = 10;
        m_shape.setFillColor(sf::Color::Red);
        break;
    case Type::Fast:
        m_speed = 100.f;
        m_damage = 5;
        m_reward = 15;
        m_shape.setFillColor(sf::Color::Yellow);
        m_shape.setSize(sf::Vector2f(25.f, 25.f));
        break;
    case Type::Tank:
        m_speed = 30.f;
        m_damage = 20;
        m_reward = 25;
        m_shape.setFillColor(sf::Color::Magenta);
        m_shape.setSize(sf::Vector2f(40.f, 40.f));
        break;
    }
}

void Enemy::update(float deltaTime)
{
    if (!m_alive || !m_target)
        return;

    // Движение к базе
    sf::Vector2f targetPos = m_target->getPosition();
    sf::Vector2f currentPos = m_shape.getPosition();
    
    // Центрируем позиции для точного расчета
    targetPos.x += m_target->getBounds().size.x / 2.f;
    targetPos.y += m_target->getBounds().size.y / 2.f;
    currentPos.x += m_shape.getSize().x / 2.f;
    currentPos.y += m_shape.getSize().y / 2.f;
    
    sf::Vector2f direction = targetPos - currentPos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    
    if (distance > 0.1f)
    {
        direction /= distance; // Нормализация
        sf::Vector2f movement = direction * m_speed * deltaTime;
        m_shape.move(movement);
    }
}

void Enemy::draw(sf::RenderWindow& window) const
{
    Entity::draw(window);
}

void Enemy::setTarget(const Base* target)
{
    m_target = target;
}

Enemy::Type Enemy::getType() const
{
    return m_type;
}

int Enemy::getDamage() const
{
    return m_damage;
}

int Enemy::getReward() const
{
    return m_reward;
}

float Enemy::getSpeed() const
{
    return m_speed;
}

