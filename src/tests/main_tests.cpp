#include "TestFramework.h"
#include "EntityTests.cpp"
#include "CollisionTests.cpp"
#include <iostream>

int main()
{
    std::cout << "=== Space Defender Unit Tests ===\n\n";
    TestFramework::runAllTests();
    return 0;
}

