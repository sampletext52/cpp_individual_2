#pragma once

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Base;

/**
 * @class Enemy
 * @brief Представляет врага, который движется к базе
 * 
 * Враги имеют разные типы и скорости движения.
 * Использует паттерн Strategy для различных типов поведения.
 */
class Enemy : public Entity
{
public:
    enum class Type
    {
        Basic,
        Fast,
        Tank
    };

    Enemy(float x, float y, Type type = Type::Basic);
    
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    
    void setTarget(const Base* target);
    Type getType() const;
    int getDamage() const;
    int getReward() const;
    float getSpeed() const;

private:
    Type m_type;
    const Base* m_target;
    float m_speed;
    int m_damage;
    int m_reward;
    
    void initializeByType();
};

