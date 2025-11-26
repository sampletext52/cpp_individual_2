#pragma once

#include "Entity.h"
#include <SFML/Graphics.hpp>

/**
 * @class Base
 * @brief Представляет базу игрока, которую нужно защищать
 * 
 * База имеет здоровье и может быть уничтожена врагами.
 */
class Base : public Entity
{
public:
    Base(float x, float y);
    
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    
    int getHealth() const;
    void takeDamage(int damage);
    bool isDestroyed() const;
    void reset();

private:
    int m_health;
    int m_maxHealth;
    static constexpr int MAX_HEALTH = 100;
};

