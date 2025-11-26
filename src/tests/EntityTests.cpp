#include "TestFramework.h"
#include "Entity.h"
#include "Base.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>

class MockEntity : public Entity
{
public:
    MockEntity(float x, float y, float width, float height)
        : Entity(x, y, width, height)
    {
    }
    
    void update(float deltaTime) override
    {
    }
};

void testEntityCreation()
{
    MockEntity entity(10.f, 20.f, 30.f, 40.f);
    
    ASSERT_TRUE(entity.isAlive());
    ASSERT_EQ(10, static_cast<int>(entity.getPosition().x));
    ASSERT_EQ(20, static_cast<int>(entity.getPosition().y));
    
    sf::FloatRect bounds = entity.getBounds();
    ASSERT_EQ(30, static_cast<int>(bounds.size.x));
    ASSERT_EQ(40, static_cast<int>(bounds.size.y));
}

void testEntitySetPosition()
{
    MockEntity entity(0.f, 0.f, 10.f, 10.f);
    
    entity.setPosition(50.f, 60.f);
    ASSERT_EQ(50, static_cast<int>(entity.getPosition().x));
    ASSERT_EQ(60, static_cast<int>(entity.getPosition().y));
}

void testEntitySetAlive()
{
    MockEntity entity(0.f, 0.f, 10.f, 10.f);
    
    ASSERT_TRUE(entity.isAlive());
    
    entity.setAlive(false);
    ASSERT_FALSE(entity.isAlive());
    
    entity.setAlive(true);
    ASSERT_TRUE(entity.isAlive());
}

void testBaseCreation()
{
    Base base(100.f, 200.f);
    
    ASSERT_TRUE(base.isAlive());
    ASSERT_EQ(100, base.getHealth());
    ASSERT_FALSE(base.isDestroyed());
    ASSERT_EQ(100, static_cast<int>(base.getPosition().x));
    ASSERT_EQ(200, static_cast<int>(base.getPosition().y));
}

void testBaseTakeDamage()
{
    Base base(0.f, 0.f);
    
    ASSERT_EQ(100, base.getHealth());
    
    base.takeDamage(30);
    ASSERT_EQ(70, base.getHealth());
    
    base.takeDamage(20);
    ASSERT_EQ(50, base.getHealth());
    
    base.takeDamage(60);
    ASSERT_EQ(0, base.getHealth());
    ASSERT_TRUE(base.isDestroyed());
}

void testBaseDestroyed()
{
    Base base(0.f, 0.f);
    
    ASSERT_FALSE(base.isDestroyed());
    
    base.takeDamage(100);
    ASSERT_TRUE(base.isDestroyed());
    
    base.takeDamage(10);
    ASSERT_EQ(0, base.getHealth());
    ASSERT_TRUE(base.isDestroyed());
}

void testBaseReset()
{
    Base base(0.f, 0.f);
    
    base.takeDamage(50);
    ASSERT_EQ(50, base.getHealth());
    
    base.reset();
    ASSERT_EQ(100, base.getHealth());
    ASSERT_FALSE(base.isDestroyed());
}

void testEnemyCreationSquare()
{
    Enemy enemy(50.f, 60.f, Enemy::Type::Square);
    
    ASSERT_TRUE(enemy.isAlive());
    ASSERT_EQ(Enemy::Type::Square, enemy.getType());
    ASSERT_EQ(Enemy::ShapeType::Square, enemy.getShapeType());
    ASSERT_EQ(40, enemy.getHealth());
    ASSERT_EQ(40, enemy.getMaxHealth());
    ASSERT_EQ(10, enemy.getDamage());
    ASSERT_EQ(15, enemy.getReward());
}

void testEnemyTypes()
{
    Enemy square(0.f, 0.f, Enemy::Type::Square);
    ASSERT_EQ(Enemy::Type::Square, square.getType());
    ASSERT_EQ(40, square.getMaxHealth());
    
    Enemy triangle(0.f, 0.f, Enemy::Type::Triangle);
    ASSERT_EQ(Enemy::Type::Triangle, triangle.getType());
    ASSERT_EQ(25, triangle.getMaxHealth());
    
    Enemy circle(0.f, 0.f, Enemy::Type::Circle);
    ASSERT_EQ(Enemy::Type::Circle, circle.getType());
    ASSERT_EQ(65, circle.getMaxHealth());
    
    Enemy pentagon(0.f, 0.f, Enemy::Type::Pentagon);
    ASSERT_EQ(Enemy::Type::Pentagon, pentagon.getType());
    ASSERT_EQ(100, pentagon.getMaxHealth());
}

void testEnemyHealth()
{
    Enemy enemy(0.f, 0.f, Enemy::Type::Square);
    
    ASSERT_EQ(40, enemy.getHealth());
    ASSERT_EQ(40, enemy.getMaxHealth());
}

void testEnemyTakeDamage()
{
    Enemy enemy(0.f, 0.f, Enemy::Type::Square);
    
    ASSERT_EQ(40, enemy.getHealth());
    
    enemy.takeDamage(15);
    ASSERT_EQ(25, enemy.getHealth());
    ASSERT_TRUE(enemy.isAlive());
    
    enemy.takeDamage(30);
    ASSERT_EQ(0, enemy.getHealth());
    ASSERT_FALSE(enemy.isAlive());
}

void testEnemyDestroyed()
{
    Enemy enemy(0.f, 0.f, Enemy::Type::Square);
    
    ASSERT_TRUE(enemy.isAlive());
    
    enemy.takeDamage(40);
    ASSERT_FALSE(enemy.isAlive());
}

void testEnemyShapeTypes()
{
    Enemy square(0.f, 0.f, Enemy::Type::Square);
    ASSERT_EQ(Enemy::ShapeType::Square, square.getShapeType());
    
    Enemy triangle(0.f, 0.f, Enemy::Type::Triangle);
    ASSERT_EQ(Enemy::ShapeType::Triangle, triangle.getShapeType());
    
    Enemy circle(0.f, 0.f, Enemy::Type::Circle);
    ASSERT_EQ(Enemy::ShapeType::Circle, circle.getShapeType());
    
    Enemy pentagon(0.f, 0.f, Enemy::Type::Pentagon);
    ASSERT_EQ(Enemy::ShapeType::Pentagon, pentagon.getShapeType());
}

void registerEntityTests()
{
    TestFramework::registerTest("Entity_Creation", testEntityCreation);
    TestFramework::registerTest("Entity_SetPosition", testEntitySetPosition);
    TestFramework::registerTest("Entity_SetAlive", testEntitySetAlive);
    TestFramework::registerTest("Base_Creation", testBaseCreation);
    TestFramework::registerTest("Base_TakeDamage", testBaseTakeDamage);
    TestFramework::registerTest("Base_Destroyed", testBaseDestroyed);
    TestFramework::registerTest("Base_Reset", testBaseReset);
    TestFramework::registerTest("Enemy_Creation_Square", testEnemyCreationSquare);
    TestFramework::registerTest("Enemy_Types", testEnemyTypes);
    TestFramework::registerTest("Enemy_Health", testEnemyHealth);
    TestFramework::registerTest("Enemy_TakeDamage", testEnemyTakeDamage);
    TestFramework::registerTest("Enemy_Destroyed", testEnemyDestroyed);
    TestFramework::registerTest("Enemy_ShapeTypes", testEnemyShapeTypes);
}
