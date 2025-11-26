#pragma once

#include <string>
#include <functional>
#include <map>
#include <iostream>
#include <cmath>
#include <type_traits>

class TestFramework
{
public:
    static void registerTest(const std::string& name, std::function<void()> test);
    static bool runTest(const std::string& name);
    static void printAllTests();

private:
    static std::map<std::string, std::function<void()>> s_tests;
    
    static void assertTrue(bool condition, const std::string& message);
    static void assertFalse(bool condition, const std::string& message);
    static void assertEquals(int expected, int actual, const std::string& message);
    static void assertEquals(float expected, float actual, float epsilon, const std::string& message);
    static void assertEquals(const std::string& expected, const std::string& actual, const std::string& message);
    
    static bool s_testPassed;
    static std::string s_currentTestName;
    
    friend class TestAssert;
};

class TestAssert
{
public:
    static void assertTrue(bool condition, const std::string& message = "");
    static void assertFalse(bool condition, const std::string& message = "");
    static void assertEquals(int expected, int actual, const std::string& message = "");
    static void assertEquals(float expected, float actual, float epsilon = 0.001f, const std::string& message = "");
    static void assertEquals(const std::string& expected, const std::string& actual, const std::string& message = "");
    
    template<typename T>
    static typename std::enable_if<std::is_enum<T>::value, void>::type
    assertEquals(T expected, T actual, const std::string& message = "")
    {
        if (expected != actual)
        {
            std::cerr << "  ASSERT_EQ failed: " << message << " (expected enum value, actual enum value)" << std::endl;
            TestFramework::s_testPassed = false;
            throw std::runtime_error("Assertion failed");
        }
    }
};

#define ASSERT_TRUE(condition) TestAssert::assertTrue(condition, #condition)
#define ASSERT_FALSE(condition) TestAssert::assertFalse(condition, #condition)
#define ASSERT_EQ(expected, actual) TestAssert::assertEquals(expected, actual, #expected " == " #actual)
#define ASSERT_EQ_FLOAT(expected, actual, epsilon) TestAssert::assertEquals(expected, actual, epsilon, #expected " == " #actual)
