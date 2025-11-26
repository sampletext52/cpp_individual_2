#pragma once

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Bullet.h"

class Enemy;

/**
 * @class Defender
 * @brief Представляет защитника, который стреляет по врагам
 * 
 * Защитники автоматически находят ближайшего врага и стреляют по нему.
 */
class Defender : public Entity
{
public:
    Defender(float x, float y);
    
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    
    void setEnemies(const std::vector<std::unique_ptr<Enemy>>* enemies);
    std::vector<std::unique_ptr<Bullet>>* getBullets();
    void clearBullets();
    
    float getRange() const;
    float getFireRate() const;

private:
    const std::vector<std::unique_ptr<Enemy>>* m_enemies;
    std::vector<std::unique_ptr<Bullet>> m_bullets;
    float m_fireCooldown;
    float m_fireRate;
    float m_range;
    
    Enemy* findNearestEnemy() const;
    float distanceTo(const sf::Vector2f& pos) const;
};

