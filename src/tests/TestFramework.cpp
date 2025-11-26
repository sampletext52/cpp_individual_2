#include "TestFramework.h"
#include <sstream>

std::vector<std::pair<std::string, std::function<bool()>>> TestFramework::s_tests;
bool TestFramework::s_currentTestPassed = true;
std::string TestFramework::s_currentTestMessage = "";

void TestFramework::runAllTests()
{
    std::cout << "Running " << s_tests.size() << " tests...\n\n";
    
    int passed = 0;
    int failed = 0;
    
    for (const auto& [name, test] : s_tests)
    {
        s_currentTestPassed = true;
        s_currentTestMessage = "";
        
        bool result = test();
        
        if (result && s_currentTestPassed)
        {
            std::cout << "[PASS] " << name << "\n";
            passed++;
        }
        else
        {
            std::cout << "[FAIL] " << name;
            if (!s_currentTestMessage.empty())
            {
                std::cout << " - " << s_currentTestMessage;
            }
            std::cout << "\n";
            failed++;
        }
    }
    
    std::cout << "\n";
    std::cout << "Tests passed: " << passed << "\n";
    std::cout << "Tests failed: " << failed << "\n";
    std::cout << "Total: " << (passed + failed) << "\n";
}

bool TestFramework::addTest(const std::string& name, std::function<bool()> test)
{
    s_tests.push_back({name, test});
    return true;
}

void TestFramework::assertTrue(bool condition, const std::string& message)
{
    if (!condition)
    {
        s_currentTestPassed = false;
        if (!message.empty())
        {
            s_currentTestMessage = message;
        }
    }
}

void TestFramework::assertFalse(bool condition, const std::string& message)
{
    assertTrue(!condition, message);
}

void TestFramework::assertEquals(int expected, int actual, const std::string& message)
{
    if (expected != actual)
    {
        s_currentTestPassed = false;
        std::ostringstream oss;
        oss << message << " (expected: " << expected << ", actual: " << actual << ")";
        s_currentTestMessage = oss.str();
    }
}

void TestFramework::assertEquals(float expected, float actual, float epsilon, const std::string& message)
{
    if (std::abs(expected - actual) > epsilon)
    {
        s_currentTestPassed = false;
        std::ostringstream oss;
        oss << message << " (expected: " << expected << ", actual: " << actual << ")";
        s_currentTestMessage = oss.str();
    }
}

