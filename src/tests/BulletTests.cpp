#include "TestFramework.h"
#include "Bullet.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>

void testBulletCreation()
{
    Bullet bullet(10.f, 20.f, 100.f, 200.f, 400.f, Enemy::Type::Square);
    
    ASSERT_TRUE(bullet.isAlive());
    ASSERT_EQ(Enemy::Type::Square, bullet.getTargetType());
    ASSERT_EQ(15, bullet.getDamage());
}

void testBulletTargetTypes()
{
    Bullet squareBullet(0.f, 0.f, 100.f, 100.f, 400.f, Enemy::Type::Square);
    ASSERT_EQ(Enemy::Type::Square, squareBullet.getTargetType());
    
    Bullet triangleBullet(0.f, 0.f, 100.f, 100.f, 400.f, Enemy::Type::Triangle);
    ASSERT_EQ(Enemy::Type::Triangle, triangleBullet.getTargetType());
    
    Bullet circleBullet(0.f, 0.f, 100.f, 100.f, 400.f, Enemy::Type::Circle);
    ASSERT_EQ(Enemy::Type::Circle, circleBullet.getTargetType());
    
    Bullet pentagonBullet(0.f, 0.f, 100.f, 100.f, 400.f, Enemy::Type::Pentagon);
    ASSERT_EQ(Enemy::Type::Pentagon, pentagonBullet.getTargetType());
}

void testBulletMovement()
{
    Bullet bullet(0.f, 0.f, 100.f, 0.f, 400.f, Enemy::Type::Square);
    
    sf::Vector2f initialPos = bullet.getPosition();
    
    bullet.update(0.1f);
    
    sf::Vector2f newPos = bullet.getPosition();
    
    ASSERT_TRUE(newPos.x > initialPos.x || newPos.y != initialPos.y);
}

void testBulletReachesTarget()
{
    Bullet bullet(95.f, 100.f, 100.f, 100.f, 400.f, Enemy::Type::Square);
    
    bool reached = false;
    for (int i = 0; i < 100; ++i)
    {
        bullet.update(0.01f);
        if (bullet.hasReachedTarget() || !bullet.isAlive())
        {
            reached = true;
            break;
        }
    }
    
    ASSERT_TRUE(reached);
}

void testBulletDamage()
{
    Bullet bullet(0.f, 0.f, 100.f, 100.f, 400.f, Enemy::Type::Square);
    
    ASSERT_EQ(15, bullet.getDamage());
}

void registerBulletTests()
{
    TestFramework::registerTest("Bullet_Creation", testBulletCreation);
    TestFramework::registerTest("Bullet_TargetTypes", testBulletTargetTypes);
    TestFramework::registerTest("Bullet_Movement", testBulletMovement);
    TestFramework::registerTest("Bullet_ReachesTarget", testBulletReachesTarget);
    TestFramework::registerTest("Bullet_Damage", testBulletDamage);
}
