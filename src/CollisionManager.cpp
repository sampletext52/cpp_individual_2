#include "CollisionManager.h"
#include "Enemy.h"
#include "Bullet.h"

int CollisionManager::checkBulletEnemyCollisions(
    std::vector<std::unique_ptr<Bullet>>& bullets,
    std::vector<std::unique_ptr<Enemy>>& enemies,
    int& score)
{
    int resourcesEarned = 0;
    for (auto& bullet : bullets)
    {
        if (!bullet->isAlive())
            continue;

        for (auto& enemy : enemies)
        {
            if (!enemy->isAlive())
                continue;

            if (checkCollision(bullet->getBounds(), enemy->getBounds()))
            {
                bullet->setAlive(false);
                resourcesEarned += enemy->getReward(); // Награда за врага
                score += enemy->getReward();
                enemy->setAlive(false);
                break;
            }
        }
    }
    return resourcesEarned;
}

void CollisionManager::checkEnemyBaseCollisions(
    std::vector<std::unique_ptr<Enemy>>& enemies,
    Base& base)
{
    for (auto& enemy : enemies)
    {
        if (!enemy->isAlive())
            continue;

        if (checkCollision(enemy->getBounds(), base.getBounds()))
        {
            base.takeDamage(enemy->getDamage());
            enemy->setAlive(false);
        }
    }
}

bool CollisionManager::checkCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2)
{
    return rect1.findIntersection(rect2).has_value();
}

