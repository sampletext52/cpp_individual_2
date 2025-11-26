#include "TestFramework.h"
#include <stdexcept>

std::map<std::string, std::function<void()>> TestFramework::s_tests;
bool TestFramework::s_testPassed = true;
std::string TestFramework::s_currentTestName;

void TestFramework::registerTest(const std::string& name, std::function<void()> test)
{
    s_tests[name] = test;
}

bool TestFramework::runTest(const std::string& name)
{
    auto it = s_tests.find(name);
    if (it == s_tests.end())
    {
        std::cerr << "Test '" << name << "' not found!" << std::endl;
        return false;
    }
    
    s_testPassed = true;
    s_currentTestName = name;
    
    try
    {
        it->second();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception in test '" << name << "': " << e.what() << std::endl;
        s_testPassed = false;
    }
    catch (...)
    {
        std::cerr << "Unknown exception in test '" << name << "'" << std::endl;
        s_testPassed = false;
    }
    
    if (s_testPassed)
    {
        std::cout << "PASS: " << name << std::endl;
        return true;
    }
    else
    {
        std::cerr << "FAIL: " << name << std::endl;
        return false;
    }
}

void TestFramework::printAllTests()
{
    std::cout << "Available tests:" << std::endl;
    for (const auto& pair : s_tests)
    {
        std::cout << "  - " << pair.first << std::endl;
    }
}

void TestFramework::assertTrue(bool condition, const std::string& message)
{
    if (!condition)
    {
        std::cerr << "  ASSERT_TRUE failed: " << message << std::endl;
        s_testPassed = false;
        throw std::runtime_error("Assertion failed");
    }
}

void TestFramework::assertFalse(bool condition, const std::string& message)
{
    if (condition)
    {
        std::cerr << "  ASSERT_FALSE failed: " << message << std::endl;
        s_testPassed = false;
        throw std::runtime_error("Assertion failed");
    }
}

void TestFramework::assertEquals(int expected, int actual, const std::string& message)
{
    if (expected != actual)
    {
        std::cerr << "  ASSERT_EQ failed: " << message << " (expected: " << expected << ", actual: " << actual << ")" << std::endl;
        s_testPassed = false;
        throw std::runtime_error("Assertion failed");
    }
}

void TestFramework::assertEquals(float expected, float actual, float epsilon, const std::string& message)
{
    if (std::abs(expected - actual) > epsilon)
    {
        std::cerr << "  ASSERT_EQ_FLOAT failed: " << message << " (expected: " << expected << ", actual: " << actual << ")" << std::endl;
        s_testPassed = false;
        throw std::runtime_error("Assertion failed");
    }
}

void TestFramework::assertEquals(const std::string& expected, const std::string& actual, const std::string& message)
{
    if (expected != actual)
    {
        std::cerr << "  ASSERT_EQ failed: " << message << " (expected: \"" << expected << "\", actual: \"" << actual << "\")" << std::endl;
        s_testPassed = false;
        throw std::runtime_error("Assertion failed");
    }
}

void TestAssert::assertTrue(bool condition, const std::string& message)
{
    TestFramework::assertTrue(condition, message);
}

void TestAssert::assertFalse(bool condition, const std::string& message)
{
    TestFramework::assertFalse(condition, message);
}

void TestAssert::assertEquals(int expected, int actual, const std::string& message)
{
    TestFramework::assertEquals(expected, actual, message);
}

void TestAssert::assertEquals(float expected, float actual, float epsilon, const std::string& message)
{
    TestFramework::assertEquals(expected, actual, epsilon, message);
}

void TestAssert::assertEquals(const std::string& expected, const std::string& actual, const std::string& message)
{
    TestFramework::assertEquals(expected, actual, message);
}
