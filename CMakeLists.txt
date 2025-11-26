cmake_minimum_required(VERSION 3.28)
project(cpp_individual_1 LANGUAGES CXX)

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Set output directories based on build type
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})

# Compiler-specific options
if(MSVC)
    # Enable debug information for Debug builds
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi")
    # Optimize for Release builds
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG")
else()
    # GCC/Clang options
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
endif()

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Main game executable
add_executable(main 
    src/main.cpp
    src/Game.cpp
    src/Game.h
    src/Entity.cpp
    src/Entity.h
    src/Base.cpp
    src/Base.h
    src/Enemy.cpp
    src/Enemy.h
    src/Bullet.cpp
    src/Bullet.h
    src/Defender.cpp
    src/Defender.h
    src/WaveManager.cpp
    src/WaveManager.h
    src/CollisionManager.cpp
    src/CollisionManager.h
    src/InputHandler.cpp
    src/InputHandler.h
)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Window)

# Test executable
add_executable(tests
    src/tests/main_tests.cpp
    src/tests/TestFramework.cpp
    src/tests/TestFramework.h
    src/tests/EntityTests.cpp
    src/tests/CollisionTests.cpp
    src/Entity.cpp
    src/Entity.h
    src/Base.cpp
    src/Base.h
    src/Enemy.cpp
    src/Enemy.h
    src/CollisionManager.cpp
    src/CollisionManager.h
)
target_compile_features(tests PRIVATE cxx_std_17)
target_link_libraries(tests PRIVATE SFML::Graphics SFML::Window)

# Set target properties
set_target_properties(main PROPERTIES
    DEBUG_POSTFIX "_debug"
    RELEASE_POSTFIX "_release"
)

# Copy SFML DLLs to output directory on Windows
if(WIN32)
    # Copy DLLs to output directory using generator expressions
    add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE_DIR:main>
        COMMENT "Copying SFML DLLs to output directory"
    )
endif()
