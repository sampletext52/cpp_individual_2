#include "TestFramework.h"
#include "WaveManager.h"
#include "Enemy.h"
#include <vector>
#include <memory>

void testWaveManagerCreation()
{
    WaveManager waveManager;
    
    ASSERT_FALSE(waveManager.isWaveActive());
    ASSERT_EQ(0, waveManager.getCurrentWave());
    ASSERT_TRUE(waveManager.hasMoreWaves());
    ASSERT_EQ(6, waveManager.getTotalWaves());
}

void testWaveManagerStartWave()
{
    WaveManager waveManager;
    
    ASSERT_FALSE(waveManager.isWaveActive());
    ASSERT_EQ(0, waveManager.getCurrentWave());
    
    waveManager.startNextWave();
    
    ASSERT_TRUE(waveManager.isWaveActive());
    ASSERT_EQ(1, waveManager.getCurrentWave());
}

void testWaveManagerReset()
{
    WaveManager waveManager;
    
    waveManager.startNextWave();
    ASSERT_TRUE(waveManager.isWaveActive());
    ASSERT_EQ(1, waveManager.getCurrentWave());
    
    waveManager.reset();
    
    ASSERT_FALSE(waveManager.isWaveActive());
    ASSERT_EQ(0, waveManager.getCurrentWave());
    ASSERT_EQ(0, static_cast<int>(waveManager.getEnemies()->size()));
}

void testWaveManagerHasMoreWaves()
{
    WaveManager waveManager;
    
    ASSERT_TRUE(waveManager.hasMoreWaves());
    
    for (int i = 0; i < 6; ++i)
    {
        waveManager.startNextWave();
    }
    
    ASSERT_FALSE(waveManager.hasMoreWaves());
}

void testWaveManagerEnemies()
{
    WaveManager waveManager;
    
    auto* enemies = waveManager.getEnemies();
    ASSERT_EQ(0, static_cast<int>(enemies->size()));
    
    waveManager.startNextWave();
    
    for (int i = 0; i < 100; ++i)
    {
        waveManager.update(0.1f);
    }
    
    ASSERT_TRUE(enemies->size() > 0);
}

void testWaveManagerCurrentWave()
{
    WaveManager waveManager;
    
    ASSERT_EQ(0, waveManager.getCurrentWave());
    
    waveManager.startNextWave();
    ASSERT_EQ(1, waveManager.getCurrentWave());
    
    waveManager.startNextWave();
    ASSERT_EQ(2, waveManager.getCurrentWave());
    
    waveManager.reset();
    ASSERT_EQ(0, waveManager.getCurrentWave());
}

void registerWaveManagerTests()
{
    TestFramework::registerTest("WaveManager_Creation", testWaveManagerCreation);
    TestFramework::registerTest("WaveManager_StartWave", testWaveManagerStartWave);
    TestFramework::registerTest("WaveManager_Reset", testWaveManagerReset);
    TestFramework::registerTest("WaveManager_HasMoreWaves", testWaveManagerHasMoreWaves);
    TestFramework::registerTest("WaveManager_Enemies", testWaveManagerEnemies);
    TestFramework::registerTest("WaveManager_CurrentWave", testWaveManagerCurrentWave);
}
