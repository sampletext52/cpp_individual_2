#pragma once

#include "Entity.h"
#include <SFML/Graphics.hpp>

/**
 * @class Bullet
 * @brief Представляет пулю, выпущенную защитником
 * 
 * Пули движутся к цели и наносят урон при попадании.
 */
class Bullet : public Entity
{
public:
    Bullet(float x, float y, float targetX, float targetY, float speed = 400.f);
    
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    
    int getDamage() const;
    bool hasReachedTarget() const;

private:
    sf::Vector2f m_velocity;
    sf::Vector2f m_target;
    float m_speed;
    static constexpr int DAMAGE = 15;
    static constexpr float TARGET_THRESHOLD = 5.f;
};

