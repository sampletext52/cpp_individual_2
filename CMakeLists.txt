cmake_minimum_required(VERSION 3.28)
project(cpp_individual_1 LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})

if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG")
else()
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

add_executable(main 
    src/main.cpp
    src/Game.cpp
    src/Entity.cpp
    src/Base.cpp
    src/Enemy.cpp
    src/Bullet.cpp
    src/Defender.cpp
    src/WaveManager.cpp
    src/CollisionManager.cpp
    src/InputHandler.cpp
)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Window)

add_executable(tests
    src/tests/main_tests.cpp
    src/tests/TestFramework.cpp
    src/tests/EntityTests.cpp
    src/tests/CollisionTests.cpp
    src/tests/DefenderTests.cpp
    src/tests/BulletTests.cpp
    src/tests/WaveManagerTests.cpp
    src/Entity.cpp
    src/Base.cpp
    src/Enemy.cpp
    src/CollisionManager.cpp
    src/Defender.cpp
    src/Bullet.cpp
    src/WaveManager.cpp
)
target_compile_features(tests PRIVATE cxx_std_17)
target_include_directories(tests PRIVATE src)
target_link_libraries(tests PRIVATE SFML::Graphics SFML::Window)

enable_testing()
add_test(NAME Entity_Creation COMMAND tests Entity_Creation)
add_test(NAME Entity_SetPosition COMMAND tests Entity_SetPosition)
add_test(NAME Entity_SetAlive COMMAND tests Entity_SetAlive)
add_test(NAME Base_Creation COMMAND tests Base_Creation)
add_test(NAME Base_TakeDamage COMMAND tests Base_TakeDamage)
add_test(NAME Base_Destroyed COMMAND tests Base_Destroyed)
add_test(NAME Base_Reset COMMAND tests Base_Reset)
add_test(NAME Enemy_Creation_Square COMMAND tests Enemy_Creation_Square)
add_test(NAME Enemy_Types COMMAND tests Enemy_Types)
add_test(NAME Enemy_Health COMMAND tests Enemy_Health)
add_test(NAME Enemy_TakeDamage COMMAND tests Enemy_TakeDamage)
add_test(NAME Enemy_Destroyed COMMAND tests Enemy_Destroyed)
add_test(NAME Enemy_ShapeTypes COMMAND tests Enemy_ShapeTypes)

add_test(NAME Collision_Intersecting COMMAND tests Collision_Intersecting)
add_test(NAME Collision_NotIntersecting COMMAND tests Collision_NotIntersecting)
add_test(NAME Collision_Touching COMMAND tests Collision_Touching)
add_test(NAME BulletEnemyCollision_SameType COMMAND tests BulletEnemyCollision_SameType)
add_test(NAME BulletEnemyCollision_DifferentType COMMAND tests BulletEnemyCollision_DifferentType)
add_test(NAME BulletEnemyCollision_Kill COMMAND tests BulletEnemyCollision_Kill)
add_test(NAME EnemyBaseCollision COMMAND tests EnemyBaseCollision)

add_test(NAME Defender_Creation COMMAND tests Defender_Creation)
add_test(NAME Defender_TargetTypes COMMAND tests Defender_TargetTypes)
add_test(NAME Defender_ShootAtSameType COMMAND tests Defender_ShootAtSameType)
add_test(NAME Defender_NoShootAtDifferentType COMMAND tests Defender_NoShootAtDifferentType)
add_test(NAME Defender_ShootAtCorrectType COMMAND tests Defender_ShootAtCorrectType)
add_test(NAME Defender_Bullets COMMAND tests Defender_Bullets)

add_test(NAME Bullet_Creation COMMAND tests Bullet_Creation)
add_test(NAME Bullet_TargetTypes COMMAND tests Bullet_TargetTypes)
add_test(NAME Bullet_Movement COMMAND tests Bullet_Movement)
add_test(NAME Bullet_ReachesTarget COMMAND tests Bullet_ReachesTarget)
add_test(NAME Bullet_Damage COMMAND tests Bullet_Damage)

add_test(NAME WaveManager_Creation COMMAND tests WaveManager_Creation)
add_test(NAME WaveManager_StartWave COMMAND tests WaveManager_StartWave)
add_test(NAME WaveManager_Reset COMMAND tests WaveManager_Reset)
add_test(NAME WaveManager_HasMoreWaves COMMAND tests WaveManager_HasMoreWaves)
add_test(NAME WaveManager_Enemies COMMAND tests WaveManager_Enemies)
add_test(NAME WaveManager_CurrentWave COMMAND tests WaveManager_CurrentWave)

set_tests_properties(
    Entity_Creation Entity_SetPosition Entity_SetAlive
    Base_Creation Base_TakeDamage Base_Destroyed Base_Reset
    Enemy_Creation_Square Enemy_Types Enemy_Health Enemy_TakeDamage Enemy_Destroyed Enemy_ShapeTypes
    Collision_Intersecting Collision_NotIntersecting Collision_Touching
    BulletEnemyCollision_SameType BulletEnemyCollision_DifferentType BulletEnemyCollision_Kill EnemyBaseCollision
    Defender_Creation Defender_TargetTypes Defender_ShootAtSameType Defender_NoShootAtDifferentType Defender_ShootAtCorrectType Defender_Bullets
    Bullet_Creation Bullet_TargetTypes Bullet_Movement Bullet_ReachesTarget Bullet_Damage
    WaveManager_Creation WaveManager_StartWave WaveManager_Reset WaveManager_HasMoreWaves WaveManager_Enemies WaveManager_CurrentWave
    PROPERTIES WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

set_target_properties(main PROPERTIES
    DEBUG_POSTFIX "_debug"
    RELEASE_POSTFIX "_release"
)

if(WIN32)
    add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE_DIR:main>
    )
endif()
