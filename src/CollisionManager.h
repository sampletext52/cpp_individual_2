#pragma once

#include "Enemy.h"
#include "Bullet.h"
#include "Base.h"
#include <vector>
#include <memory>
#include <algorithm>

class CollisionManager
{
public:
    static int checkBulletEnemyCollisions(
        std::vector<std::unique_ptr<Bullet>>& bullets,
        std::vector<std::unique_ptr<Enemy>>& enemies,
        int& score
    );
    
    static void checkEnemyBaseCollisions(
        std::vector<std::unique_ptr<Enemy>>& enemies,
        Base& base
    );
    
    static bool checkCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
};

