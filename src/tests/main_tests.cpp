#include "TestFramework.h"
#include <iostream>
#include <string>

void registerEntityTests();
void registerCollisionTests();
void registerDefenderTests();
void registerBulletTests();
void registerWaveManagerTests();

int main(int argc, char* argv[])
{
    registerEntityTests();
    registerCollisionTests();
    registerDefenderTests();
    registerBulletTests();
    registerWaveManagerTests();
    
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <test_name>" << std::endl;
        std::cerr << "Or: " << argv[0] << " --list" << std::endl;
        TestFramework::printAllTests();
        return 1;
    }
    
    std::string testName = argv[1];
    
    if (testName == "--list")
    {
        TestFramework::printAllTests();
        return 0;
    }
    
    bool passed = TestFramework::runTest(testName);
    return passed ? 0 : 1;
}
