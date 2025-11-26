#include "Defender.h"
#include "Enemy.h"
#include <cmath>
#include <algorithm>
#include <limits>

Defender::Defender(float x, float y, Enemy::Type targetType)
    : Entity(x, y, 20.f, 20.f)
    , m_targetType(targetType)
    , m_enemies(nullptr)
    , m_fireCooldown(0.f)
    , m_fireRate(1.5f)
    , m_range(200.f)
{
    switch (m_targetType)
    {
    case Enemy::Type::Square:
        m_shape.setFillColor(sf::Color::Green);
        break;
    case Enemy::Type::Triangle:
        m_shape.setFillColor(sf::Color(255, 200, 0));
        break;
    case Enemy::Type::Circle:
        m_shape.setFillColor(sf::Color(0, 200, 255));
        break;
    case Enemy::Type::Pentagon:
        m_shape.setFillColor(sf::Color(255, 0, 255));
        break;
    }
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setOutlineThickness(1.f);
}

void Defender::update(float deltaTime)
{
    if (!m_alive || !m_enemies)
        return;

    m_fireCooldown -= deltaTime;

    if (m_fireCooldown <= 0.f)
    {
        Enemy* nearest = findNearestEnemy();
        if (nearest && nearest->isAlive())
        {
            float dist = distanceTo(nearest->getPosition());
            if (dist <= m_range)
            {
                sf::Vector2f enemyPos = nearest->getPosition();
                enemyPos.x += nearest->getBounds().size.x / 2.f;
                enemyPos.y += nearest->getBounds().size.y / 2.f;
                
                sf::Vector2f defenderPos = m_shape.getPosition();
                defenderPos.x += m_shape.getSize().x / 2.f;
                defenderPos.y += m_shape.getSize().y / 2.f;
                
                m_bullets.push_back(std::make_unique<Bullet>(
                    defenderPos.x, defenderPos.y,
                    enemyPos.x, enemyPos.y,
                    400.f,
                    m_targetType
                ));
                
                m_fireCooldown = 1.f / m_fireRate;
            }
        }
    }

    for (auto& bullet : m_bullets)
    {
        bullet->update(deltaTime);
    }

    m_bullets.erase(
        std::remove_if(m_bullets.begin(), m_bullets.end(),
            [](const std::unique_ptr<Bullet>& b) { return !b->isAlive(); }),
        m_bullets.end()
    );
}

void Defender::draw(sf::RenderWindow& window) const
{
    Entity::draw(window);
    
    for (const auto& bullet : m_bullets)
    {
        bullet->draw(window);
    }
}

void Defender::setEnemies(const std::vector<std::unique_ptr<Enemy>>* enemies)
{
    m_enemies = enemies;
}

std::vector<std::unique_ptr<Bullet>>* Defender::getBullets()
{
    return &m_bullets;
}

void Defender::clearBullets()
{
    m_bullets.clear();
}

float Defender::getRange() const
{
    return m_range;
}

float Defender::getFireRate() const
{
    return m_fireRate;
}

Enemy* Defender::findNearestEnemy() const
{
    if (!m_enemies || m_enemies->empty())
        return nullptr;

    Enemy* nearest = nullptr;
    float minDistance = std::numeric_limits<float>::max();
    sf::Vector2f defenderPos = m_shape.getPosition();
    defenderPos.x += m_shape.getSize().x / 2.f;
    defenderPos.y += m_shape.getSize().y / 2.f;

    for (const auto& enemy : *m_enemies)
    {
        if (!enemy->isAlive())
            continue;
        
        if (enemy->getType() != m_targetType)
            continue;

        float dist = distanceTo(enemy->getPosition());
        if (dist < minDistance)
        {
            minDistance = dist;
            nearest = enemy.get();
        }
    }

    return nearest;
}

float Defender::distanceTo(const sf::Vector2f& pos) const
{
    sf::Vector2f defenderPos = m_shape.getPosition();
    defenderPos.x += m_shape.getSize().x / 2.f;
    defenderPos.y += m_shape.getSize().y / 2.f;
    
    sf::Vector2f diff = pos - defenderPos;
    return std::sqrt(diff.x * diff.x + diff.y * diff.y);
}

Enemy::Type Defender::getTargetType() const
{
    return m_targetType;
}
