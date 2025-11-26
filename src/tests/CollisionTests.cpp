#include "TestFramework.h"
#include "CollisionManager.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Base.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

void testCollisionIntersecting()
{
    sf::FloatRect rect1(sf::Vector2f(10.f, 10.f), sf::Vector2f(20.f, 20.f));
    sf::FloatRect rect2(sf::Vector2f(15.f, 15.f), sf::Vector2f(20.f, 20.f));
    
    ASSERT_TRUE(CollisionManager::checkCollision(rect1, rect2));
}

void testCollisionNotIntersecting()
{
    sf::FloatRect rect1(sf::Vector2f(10.f, 10.f), sf::Vector2f(20.f, 20.f));
    sf::FloatRect rect2(sf::Vector2f(50.f, 50.f), sf::Vector2f(20.f, 20.f));
    
    ASSERT_FALSE(CollisionManager::checkCollision(rect1, rect2));
}

void testCollisionTouching()
{
    sf::FloatRect rect1(sf::Vector2f(10.f, 10.f), sf::Vector2f(20.f, 20.f));
    sf::FloatRect rect2(sf::Vector2f(25.f, 10.f), sf::Vector2f(20.f, 20.f));
    
    ASSERT_TRUE(CollisionManager::checkCollision(rect1, rect2));
}

void testBulletEnemyCollisionSameType()
{
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<Enemy>> enemies;
    int score = 0;
    
    auto bullet = std::make_unique<Bullet>(100.f, 100.f, 100.f, 100.f, 400.f, Enemy::Type::Square);
    auto enemy = std::make_unique<Enemy>(100.f, 100.f, Enemy::Type::Square);
    
    bullets.push_back(std::move(bullet));
    enemies.push_back(std::move(enemy));
    
    int resources = CollisionManager::checkBulletEnemyCollisions(bullets, enemies, score);
    
    ASSERT_TRUE(bullets[0]->isAlive() == false || enemies[0]->getHealth() < enemies[0]->getMaxHealth());
}

void testBulletEnemyCollisionDifferentType()
{
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<Enemy>> enemies;
    int score = 0;
    
    auto bullet = std::make_unique<Bullet>(100.f, 100.f, 100.f, 100.f, 400.f, Enemy::Type::Square);
    auto enemy = std::make_unique<Enemy>(100.f, 100.f, Enemy::Type::Triangle);
    
    int initialHealth = enemy->getHealth();
    
    bullets.push_back(std::move(bullet));
    enemies.push_back(std::move(enemy));
    
    int resources = CollisionManager::checkBulletEnemyCollisions(bullets, enemies, score);
    
    ASSERT_EQ(initialHealth, enemies[0]->getHealth());
    ASSERT_EQ(0, resources);
}

void testBulletEnemyCollisionKill()
{
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<Enemy>> enemies;
    int score = 0;
    
    auto enemy = std::make_unique<Enemy>(100.f, 100.f, Enemy::Type::Square);
    enemy->takeDamage(35);
    
    int reward = enemy->getReward();
    
    auto bullet = std::make_unique<Bullet>(100.f, 100.f, 100.f, 100.f, 400.f, Enemy::Type::Square);
    
    bullets.push_back(std::move(bullet));
    enemies.push_back(std::move(enemy));
    
    int resources = CollisionManager::checkBulletEnemyCollisions(bullets, enemies, score);
    
    ASSERT_FALSE(enemies[0]->isAlive());
    ASSERT_EQ(reward, resources);
    ASSERT_EQ(reward, score);
}

void testEnemyBaseCollision()
{
    std::vector<std::unique_ptr<Enemy>> enemies;
    Base base(100.f, 100.f);
    
    int initialHealth = base.getHealth();
    int enemyDamage = 10;
    
    auto enemy = std::make_unique<Enemy>(100.f, 100.f, Enemy::Type::Square);
    enemyDamage = enemy->getDamage();
    
    enemies.push_back(std::move(enemy));
    
    CollisionManager::checkEnemyBaseCollisions(enemies, base);
    
    ASSERT_EQ(initialHealth - enemyDamage, base.getHealth());
    ASSERT_FALSE(enemies[0]->isAlive());
}

void registerCollisionTests()
{
    TestFramework::registerTest("Collision_Intersecting", testCollisionIntersecting);
    TestFramework::registerTest("Collision_NotIntersecting", testCollisionNotIntersecting);
    TestFramework::registerTest("Collision_Touching", testCollisionTouching);
    TestFramework::registerTest("BulletEnemyCollision_SameType", testBulletEnemyCollisionSameType);
    TestFramework::registerTest("BulletEnemyCollision_DifferentType", testBulletEnemyCollisionDifferentType);
    TestFramework::registerTest("BulletEnemyCollision_Kill", testBulletEnemyCollisionKill);
    TestFramework::registerTest("EnemyBaseCollision", testEnemyBaseCollision);
}
