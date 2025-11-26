#include "Enemy.h"
#include "Base.h"
#include <cmath>
#include <algorithm>

Enemy::Enemy(float x, float y, Type type)
    : Entity(x, y, 30.f, 30.f)
    , m_type(type)
    , m_shapeType(ShapeType::Square)
    , m_target(nullptr)
    , m_speed(50.f)
    , m_damage(10)
    , m_reward(10)
    , m_size(30.f)
    , m_health(100)
    , m_maxHealth(100)
{
    initializeByType();
}

void Enemy::initializeByType()
{
    switch (m_type)
    {
    case Type::Square:
        m_shapeType = ShapeType::Square;
        m_speed = 50.f;
        m_damage = 10;
        m_reward = 15;
        m_size = 30.f;
        m_maxHealth = 40;
        m_health = m_maxHealth;
        m_shape.setFillColor(sf::Color::Red);
        m_shape.setSize(sf::Vector2f(m_size, m_size));
        break;
    case Type::Triangle:
        m_shapeType = ShapeType::Triangle;
        m_speed = 100.f;
        m_damage = 5;
        m_reward = 20;
        m_size = 30.f;
        m_maxHealth = 25;
        m_health = m_maxHealth;
        m_shape.setFillColor(sf::Color::Yellow);
        m_shape.setSize(sf::Vector2f(m_size, m_size));
        break;
    case Type::Circle:
        m_shapeType = ShapeType::Circle;
        m_speed = 70.f;
        m_damage = 15;
        m_reward = 30;
        m_size = 30.f;
        m_maxHealth = 65;
        m_health = m_maxHealth;
        m_shape.setFillColor(sf::Color::Cyan);
        m_shape.setSize(sf::Vector2f(m_size, m_size));
        break;
    case Type::Pentagon:
        m_shapeType = ShapeType::Pentagon;
        m_speed = 30.f;
        m_damage = 25;
        m_reward = 45;
        m_size = 35.f;
        m_maxHealth = 100;
        m_health = m_maxHealth;
        m_shape.setFillColor(sf::Color::Magenta);
        m_shape.setSize(sf::Vector2f(m_size, m_size));
        break;
    }
}

void Enemy::update(float deltaTime)
{
    if (!m_alive || !m_target)
        return;

    sf::Vector2f targetPos = m_target->getPosition();
    sf::Vector2f currentPos = m_shape.getPosition();
    
    targetPos.x += m_target->getBounds().size.x / 2.f;
    targetPos.y += m_target->getBounds().size.y / 2.f;
    currentPos.x += m_shape.getSize().x / 2.f;
    currentPos.y += m_shape.getSize().y / 2.f;
    
    sf::Vector2f direction = targetPos - currentPos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    
    if (distance > 0.1f)
    {
        direction /= distance;
        sf::Vector2f movement = direction * m_speed * deltaTime;
        m_shape.move(movement);
    }
}

void Enemy::draw(sf::RenderWindow& window) const
{
    if (!m_alive)
        return;
    
    drawShape(window);
    
    if (isDamaged())
    {
        drawHealthBar(window);
    }
}

void Enemy::drawShape(sf::RenderWindow& window) const
{
    sf::Vector2f pos = m_shape.getPosition();
    sf::Color color = m_shape.getFillColor();
    
    if (isDamaged())
    {
        color.r = std::min(255, color.r + 50);
        color.g = std::min(255, color.g + 50);
        color.b = std::min(255, color.b + 50);
    }
    
    switch (m_shapeType)
    {
    case ShapeType::Square:
    {
        sf::RectangleShape square(sf::Vector2f(m_size, m_size));
        square.setPosition(pos);
        square.setFillColor(color);
        square.setOutlineColor(isDamaged() ? sf::Color(255, 255, 100) : sf::Color::White);
        square.setOutlineThickness(isDamaged() ? 2.f : 1.f);
        window.draw(square);
        break;
    }
    case ShapeType::Triangle:
    {
        sf::CircleShape triangle(m_size / 2.f, 3);
        triangle.setPosition(pos);
        triangle.setFillColor(color);
        triangle.setOutlineColor(isDamaged() ? sf::Color(255, 255, 100) : sf::Color::White);
        triangle.setOutlineThickness(isDamaged() ? 2.f : 1.f);
        window.draw(triangle);
        break;
    }
    case ShapeType::Circle:
    {
        sf::CircleShape circle(m_size / 2.f);
        circle.setPosition(pos);
        circle.setFillColor(color);
        circle.setOutlineColor(isDamaged() ? sf::Color(255, 255, 100) : sf::Color::White);
        circle.setOutlineThickness(isDamaged() ? 2.f : 1.f);
        window.draw(circle);
        break;
    }
    case ShapeType::Pentagon:
    {
        sf::CircleShape pentagon(m_size / 2.f, 5);
        pentagon.setPosition(pos);
        pentagon.setFillColor(color);
        pentagon.setOutlineColor(isDamaged() ? sf::Color(255, 255, 100) : sf::Color::White);
        pentagon.setOutlineThickness(isDamaged() ? 2.f : 1.f);
        window.draw(pentagon);
        break;
    }
    }
}

void Enemy::drawHealthBar(sf::RenderWindow& window) const
{
    sf::Vector2f pos = m_shape.getPosition();
    float barWidth = m_size;
    float barHeight = 4.f;
    float barX = pos.x;
    float barY = pos.y - 8.f;
    
    sf::RectangleShape background(sf::Vector2f(barWidth, barHeight));
    background.setPosition(sf::Vector2f(barX, barY));
    background.setFillColor(sf::Color::Black);
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(0.5f);
    window.draw(background);
    
    float healthPercent = static_cast<float>(m_health) / static_cast<float>(m_maxHealth);
    float healthWidth = barWidth * healthPercent;
    
    if (healthWidth > 0.f)
    {
        sf::RectangleShape healthBar(sf::Vector2f(healthWidth, barHeight));
        healthBar.setPosition(sf::Vector2f(barX, barY));
        
        if (healthPercent > 0.6f)
            healthBar.setFillColor(sf::Color::Green);
        else if (healthPercent > 0.3f)
            healthBar.setFillColor(sf::Color::Yellow);
        else
            healthBar.setFillColor(sf::Color::Red);
        
        window.draw(healthBar);
    }
}

void Enemy::setTarget(const Base* target)
{
    m_target = target;
}

Enemy::Type Enemy::getType() const
{
    return m_type;
}

Enemy::ShapeType Enemy::getShapeType() const
{
    return m_shapeType;
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

void Enemy::takeDamage(int damage)
{
    m_health -= damage;
    if (m_health <= 0)
    {
        m_health = 0;
        m_alive = false;
    }
}

int Enemy::getHealth() const
{
    return m_health;
}

int Enemy::getMaxHealth() const
{
    return m_maxHealth;
}

bool Enemy::isDamaged() const
{
    return m_health < m_maxHealth;
}
