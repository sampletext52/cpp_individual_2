#pragma once

#include "Enemy.h"
#include <vector>
#include <memory>
#include <map>
#include <functional>
#include <chrono>

class WaveManager
{
public:
    struct WaveConfig
    {
        int enemyCount;
        float spawnInterval;
        Enemy::Type enemyType;
    };

    WaveManager();
    
    void update(float deltaTime);
    bool isWaveActive() const;
    bool hasMoreWaves() const;
    void startNextWave();
    void reset();
    
    std::vector<std::unique_ptr<Enemy>>* getEnemies();
    int getCurrentWave() const;
    int getTotalWaves() const;
    
    void addCustomWave(const std::vector<WaveConfig>& config);

private:
    std::vector<std::vector<WaveConfig>> m_waves;
    std::vector<std::unique_ptr<Enemy>> m_enemies;
    int m_currentWave;
    float m_spawnTimer;
    int m_enemiesSpawnedInWave;
    bool m_waveActive;
    
    void initializeWaves();
    void spawnEnemy(const WaveConfig& config);
};

