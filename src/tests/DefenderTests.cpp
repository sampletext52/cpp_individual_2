#include "TestFramework.h"
#include "Defender.h"
#include "Enemy.h"
#include "Base.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

void testDefenderCreation()
{
    Defender defender(50.f, 60.f, Enemy::Type::Square);
    
    ASSERT_TRUE(defender.isAlive());
    ASSERT_EQ(Enemy::Type::Square, defender.getTargetType());
    ASSERT_EQ(200, static_cast<int>(defender.getRange()));
    ASSERT_EQ(1, static_cast<int>(defender.getFireRate()));
}

void testDefenderTargetTypes()
{
    Defender squareDefender(0.f, 0.f, Enemy::Type::Square);
    ASSERT_EQ(Enemy::Type::Square, squareDefender.getTargetType());
    
    Defender triangleDefender(0.f, 0.f, Enemy::Type::Triangle);
    ASSERT_EQ(Enemy::Type::Triangle, triangleDefender.getTargetType());
    
    Defender circleDefender(0.f, 0.f, Enemy::Type::Circle);
    ASSERT_EQ(Enemy::Type::Circle, circleDefender.getTargetType());
    
    Defender pentagonDefender(0.f, 0.f, Enemy::Type::Pentagon);
    ASSERT_EQ(Enemy::Type::Pentagon, pentagonDefender.getTargetType());
}

void testDefenderShootAtSameType()
{
    Defender defender(100.f, 100.f, Enemy::Type::Square);
    
    std::vector<std::unique_ptr<Enemy>> enemies;
    auto enemy = std::make_unique<Enemy>(150.f, 100.f, Enemy::Type::Square);
    Base base(200.f, 200.f);
    enemy->setTarget(&base);
    
    enemies.push_back(std::move(enemy));
    defender.setEnemies(&enemies);
    
    for (int i = 0; i < 100; ++i)
    {
        defender.update(0.1f);
    }
    
    auto* bullets = defender.getBullets();
    ASSERT_TRUE(bullets->size() > 0);
}

void testDefenderNoShootAtDifferentType()
{
    Defender defender(100.f, 100.f, Enemy::Type::Square);
    
    std::vector<std::unique_ptr<Enemy>> enemies;
    auto enemy = std::make_unique<Enemy>(150.f, 100.f, Enemy::Type::Triangle);
    Base base(200.f, 200.f);
    enemy->setTarget(&base);
    
    enemies.push_back(std::move(enemy));
    defender.setEnemies(&enemies);
    
    for (int i = 0; i < 100; ++i)
    {
        defender.update(0.1f);
    }
    
    auto* bullets = defender.getBullets();
    ASSERT_EQ(0, static_cast<int>(bullets->size()));
}

void testDefenderShootAtCorrectType()
{
    Defender defender(100.f, 100.f, Enemy::Type::Circle);
    
    std::vector<std::unique_ptr<Enemy>> enemies;
    
    auto squareEnemy = std::make_unique<Enemy>(150.f, 100.f, Enemy::Type::Square);
    auto triangleEnemy = std::make_unique<Enemy>(150.f, 120.f, Enemy::Type::Triangle);
    auto circleEnemy = std::make_unique<Enemy>(150.f, 140.f, Enemy::Type::Circle);
    
    Base base(200.f, 200.f);
    squareEnemy->setTarget(&base);
    triangleEnemy->setTarget(&base);
    circleEnemy->setTarget(&base);
    
    enemies.push_back(std::move(squareEnemy));
    enemies.push_back(std::move(triangleEnemy));
    enemies.push_back(std::move(circleEnemy));
    
    defender.setEnemies(&enemies);
    
    for (int i = 0; i < 100; ++i)
    {
        defender.update(0.1f);
    }
    
    auto* bullets = defender.getBullets();
    ASSERT_TRUE(bullets->size() > 0);
    
    for (const auto& bullet : *bullets)
    {
        ASSERT_EQ(Enemy::Type::Circle, bullet->getTargetType());
    }
}

void testDefenderBullets()
{
    Defender defender(0.f, 0.f, Enemy::Type::Square);
    
    auto* bullets = defender.getBullets();
    ASSERT_EQ(0, static_cast<int>(bullets->size()));
    
    defender.clearBullets();
    ASSERT_EQ(0, static_cast<int>(bullets->size()));
}

void registerDefenderTests()
{
    TestFramework::registerTest("Defender_Creation", testDefenderCreation);
    TestFramework::registerTest("Defender_TargetTypes", testDefenderTargetTypes);
    TestFramework::registerTest("Defender_ShootAtSameType", testDefenderShootAtSameType);
    TestFramework::registerTest("Defender_NoShootAtDifferentType", testDefenderNoShootAtDifferentType);
    TestFramework::registerTest("Defender_ShootAtCorrectType", testDefenderShootAtCorrectType);
    TestFramework::registerTest("Defender_Bullets", testDefenderBullets);
}
