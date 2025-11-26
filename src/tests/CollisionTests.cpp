#include "TestFramework.h"
#include "../CollisionManager.h"
#include <SFML/Graphics.hpp>

TEST(Collision_Intersecting)
{
    sf::FloatRect rect1(0.f, 0.f, 50.f, 50.f);
    sf::FloatRect rect2(25.f, 25.f, 50.f, 50.f);
    ASSERT_TRUE(CollisionManager::checkCollision(rect1, rect2));
    return true;
}

TEST(Collision_NotIntersecting)
{
    sf::FloatRect rect1(0.f, 0.f, 50.f, 50.f);
    sf::FloatRect rect2(100.f, 100.f, 50.f, 50.f);
    ASSERT_FALSE(CollisionManager::checkCollision(rect1, rect2));
    return true;
}

TEST(Collision_Touching)
{
    sf::FloatRect rect1(0.f, 0.f, 50.f, 50.f);
    sf::FloatRect rect2(50.f, 0.f, 50.f, 50.f);
    ASSERT_TRUE(CollisionManager::checkCollision(rect1, rect2));
    return true;
}

