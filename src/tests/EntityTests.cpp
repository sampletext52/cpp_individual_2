#include "TestFramework.h"
#include "../Entity.h"
#include "../Base.h"
#include "../Enemy.h"
#include <cmath>

TEST(Entity_Creation)
{
    Entity entity(10.f, 20.f, 30.f, 40.f);
    ASSERT_TRUE(entity.isAlive());
    ASSERT_TRUE(entity.getPosition().x == 10.f);
    ASSERT_TRUE(entity.getPosition().y == 20.f);
    return true;
}

TEST(Entity_SetPosition)
{
    Entity entity(0.f, 0.f, 10.f, 10.f);
    entity.setPosition(50.f, 60.f);
    ASSERT_TRUE(entity.getPosition().x == 50.f);
    ASSERT_TRUE(entity.getPosition().y == 60.f);
    return true;
}

TEST(Entity_SetAlive)
{
    Entity entity(0.f, 0.f, 10.f, 10.f);
    entity.setAlive(false);
    ASSERT_FALSE(entity.isAlive());
    return true;
}

TEST(Base_Creation)
{
    Base base(100.f, 200.f);
    ASSERT_TRUE(base.getHealth() == 100);
    ASSERT_FALSE(base.isDestroyed());
    return true;
}

TEST(Base_TakeDamage)
{
    Base base(0.f, 0.f);
    base.takeDamage(30);
    ASSERT_EQUALS(70, base.getHealth());
    base.takeDamage(50);
    ASSERT_EQUALS(20, base.getHealth());
    return true;
}

TEST(Base_Destroyed)
{
    Base base(0.f, 0.f);
    base.takeDamage(100);
    ASSERT_TRUE(base.isDestroyed());
    return true;
}

TEST(Enemy_Creation)
{
    Enemy enemy(0.f, 0.f, Enemy::Type::Basic);
    ASSERT_TRUE(enemy.getType() == Enemy::Type::Basic);
    ASSERT_TRUE(enemy.getDamage() > 0);
    ASSERT_TRUE(enemy.getReward() > 0);
    return true;
}

TEST(Enemy_Types)
{
    Enemy basic(0.f, 0.f, Enemy::Type::Basic);
    Enemy fast(0.f, 0.f, Enemy::Type::Fast);
    Enemy tank(0.f, 0.f, Enemy::Type::Tank);
    
    ASSERT_TRUE(fast.getSpeed() > basic.getSpeed());
    ASSERT_TRUE(tank.getDamage() > basic.getDamage());
    return true;
}

