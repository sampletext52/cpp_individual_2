#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <functional>

/**
 * @class TestFramework
 * @brief Простой фреймворк для unit тестирования
 * 
 * Демонстрирует использование STD функциональных объектов и контейнеров.
 */
class TestFramework
{
public:
    struct TestResult
    {
        std::string name;
        bool passed;
        std::string message;
    };

    static void runAllTests();
    static bool addTest(const std::string& name, std::function<bool()> test);
    
    static void assertTrue(bool condition, const std::string& message = "");
    static void assertFalse(bool condition, const std::string& message = "");
    static void assertEquals(int expected, int actual, const std::string& message = "");
    static void assertEquals(float expected, float actual, float epsilon = 0.001f, const std::string& message = "");

private:
    static std::vector<std::pair<std::string, std::function<bool()>>> s_tests;
    static bool s_currentTestPassed;
    static std::string s_currentTestMessage;
};

#define TEST(name) \
    bool test_##name(); \
    static bool _registered_##name = TestFramework::addTest(#name, test_##name); \
    bool test_##name()

#define ASSERT_TRUE(condition) TestFramework::assertTrue(condition, #condition)
#define ASSERT_FALSE(condition) TestFramework::assertFalse(condition, #condition)
#define ASSERT_EQUALS(expected, actual) TestFramework::assertEquals(expected, actual, #expected " == " #actual)

