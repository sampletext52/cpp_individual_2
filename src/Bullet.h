#pragma once

#include "Entity.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>

class Bullet : public Entity
{
public:
    Bullet(float x, float y, float targetX, float targetY, float speed = 400.f, Enemy::Type targetType = Enemy::Type::Square);
    
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    
    int getDamage() const;
    bool hasReachedTarget() const;
    Enemy::Type getTargetType() const;

private:
    sf::Vector2f m_velocity;
    sf::Vector2f m_target;
    float m_speed;
    Enemy::Type m_targetType;
    static constexpr int DAMAGE = 15;
    static constexpr float TARGET_THRESHOLD = 5.f;
};

