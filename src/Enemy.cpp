#include "Enemy.h"
#include "Base.h"
#include <cmath>

Enemy::Enemy(float x, float y, Type type)
    : Entity(x, y, 30.f, 30.f)
    , m_type(type)
    , m_shapeType(ShapeType::Square)
    , m_target(nullptr)
    , m_speed(50.f)
    , m_damage(10)
    , m_reward(10)
    , m_size(30.f)
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
        m_reward = 10;
        m_size = 30.f;
        m_shape.setFillColor(sf::Color::Red);
        m_shape.setSize(sf::Vector2f(m_size, m_size));
        break;
    case Type::Triangle:
        m_shapeType = ShapeType::Triangle;
        m_speed = 100.f;
        m_damage = 5;
        m_reward = 15;
        m_size = 30.f;
        m_shape.setFillColor(sf::Color::Yellow);
        m_shape.setSize(sf::Vector2f(m_size, m_size));
        break;
    case Type::Circle:
        m_shapeType = ShapeType::Circle;
        m_speed = 70.f;
        m_damage = 15;
        m_reward = 20;
        m_size = 30.f;
        m_shape.setFillColor(sf::Color::Cyan);
        m_shape.setSize(sf::Vector2f(m_size, m_size));
        break;
    case Type::Pentagon:
        m_shapeType = ShapeType::Pentagon;
        m_speed = 30.f;
        m_damage = 25;
        m_reward = 30;
        m_size = 35.f;
        m_shape.setFillColor(sf::Color::Magenta);
        m_shape.setSize(sf::Vector2f(m_size, m_size));
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
    if (!m_alive)
        return;
    
    drawShape(window);
}

void Enemy::drawShape(sf::RenderWindow& window) const
{
    sf::Vector2f pos = m_shape.getPosition();
    sf::Color color = m_shape.getFillColor();
    
    switch (m_shapeType)
    {
    case ShapeType::Square:
    {
        sf::RectangleShape square(sf::Vector2f(m_size, m_size));
        square.setPosition(pos);
        square.setFillColor(color);
        square.setOutlineColor(sf::Color::White);
        square.setOutlineThickness(1.f);
        window.draw(square);
        break;
    }
    case ShapeType::Triangle:
    {
        sf::CircleShape triangle(m_size / 2.f, 3); // 3 вершины = треугольник
        triangle.setPosition(pos);
        triangle.setFillColor(color);
        triangle.setOutlineColor(sf::Color::White);
        triangle.setOutlineThickness(1.f);
        window.draw(triangle);
        break;
    }
    case ShapeType::Circle:
    {
        sf::CircleShape circle(m_size / 2.f);
        circle.setPosition(pos);
        circle.setFillColor(color);
        circle.setOutlineColor(sf::Color::White);
        circle.setOutlineThickness(1.f);
        window.draw(circle);
        break;
    }
    case ShapeType::Pentagon:
    {
        sf::CircleShape pentagon(m_size / 2.f, 5); // 5 вершин = пятиугольник
        pentagon.setPosition(pos);
        pentagon.setFillColor(color);
        pentagon.setOutlineColor(sf::Color::White);
        pentagon.setOutlineThickness(1.f);
        window.draw(pentagon);
        break;
    }
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

