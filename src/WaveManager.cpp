#include "WaveManager.h"
#include <algorithm>
#include <random>
#include <ctime>

WaveManager::WaveManager()
    : m_currentWave(0)
    , m_spawnTimer(0.f)
    , m_enemiesSpawnedInWave(0)
    , m_waveActive(false)
{
    initializeWaves();
}

void WaveManager::update(float deltaTime)
{
    if (!m_waveActive || m_currentWave == 0 || m_currentWave > static_cast<int>(m_waves.size()))
        return;

    const auto& wave = m_waves[m_currentWave - 1];
    
    if (m_enemiesSpawnedInWave < static_cast<int>(wave.size()))
    {
        m_spawnTimer -= deltaTime;
        
        if (m_spawnTimer <= 0.f)
        {
            spawnEnemy(wave[m_enemiesSpawnedInWave]);
            m_enemiesSpawnedInWave++;
            
            if (m_enemiesSpawnedInWave < static_cast<int>(wave.size()))
            {
                m_spawnTimer = wave[m_enemiesSpawnedInWave].spawnInterval;
            }
        }
    }
    
    m_enemies.erase(
        std::remove_if(m_enemies.begin(), m_enemies.end(),
            [](const std::unique_ptr<Enemy>& e) { return !e->isAlive(); }),
        m_enemies.end()
    );
    
    if (m_enemiesSpawnedInWave >= static_cast<int>(wave.size()) && m_enemies.empty())
    {
        m_waveActive = false;
    }
}

bool WaveManager::isWaveActive() const
{
    return m_waveActive;
}

bool WaveManager::hasMoreWaves() const
{
    return m_currentWave < static_cast<int>(m_waves.size());
}

void WaveManager::startNextWave()
{
    if (m_currentWave >= static_cast<int>(m_waves.size()))
        return;
    
    if (m_waves[m_currentWave].empty())
    {
        m_currentWave++;
        return;
    }

    m_waveActive = true;
    m_enemiesSpawnedInWave = 0;
    m_spawnTimer = m_waves[m_currentWave][0].spawnInterval;
    
    m_currentWave++;
}

void WaveManager::reset()
{
    m_currentWave = 0;
    m_spawnTimer = 0.f;
    m_enemiesSpawnedInWave = 0;
    m_waveActive = false;
    m_enemies.clear();
}

std::vector<std::unique_ptr<Enemy>>* WaveManager::getEnemies()
{
    return &m_enemies;
}

int WaveManager::getCurrentWave() const
{
    if (m_currentWave == 0 && !m_waveActive)
        return 0;
    return m_currentWave;
}

int WaveManager::getTotalWaves() const
{
    return static_cast<int>(m_waves.size());
}

void WaveManager::addCustomWave(const std::vector<WaveConfig>& config)
{
    m_waves.push_back(config);
}

void WaveManager::initializeWaves()
{
    m_waves.push_back({
        {3, 1.3f, Enemy::Type::Square},
        {3, 1.1f, Enemy::Type::Square},
        {2, 1.0f, Enemy::Type::Square},
        {2, 0.9f, Enemy::Type::Square}
    });
    
    m_waves.push_back({
        {2, 1.1f, Enemy::Type::Square},
        {2, 0.9f, Enemy::Type::Triangle},
        {2, 1.0f, Enemy::Type::Square},
        {2, 0.9f, Enemy::Type::Triangle},
        {2, 0.8f, Enemy::Type::Square}
    });
    
    m_waves.push_back({
        {2, 1.3f, Enemy::Type::Circle},
        {2, 1.1f, Enemy::Type::Square},
        {2, 1.0f, Enemy::Type::Triangle},
        {2, 0.9f, Enemy::Type::Circle},
        {3, 0.8f, Enemy::Type::Square}
    });
    
    m_waves.push_back({
        {1, 1.6f, Enemy::Type::Pentagon},
        {2, 0.9f, Enemy::Type::Triangle},
        {2, 1.1f, Enemy::Type::Square},
        {2, 0.8f, Enemy::Type::Circle},
        {2, 1.3f, Enemy::Type::Pentagon},
        {3, 0.7f, Enemy::Type::Triangle}
    });
    
    m_waves.push_back({
        {2, 1.6f, Enemy::Type::Pentagon},
        {3, 0.7f, Enemy::Type::Triangle},
        {2, 0.9f, Enemy::Type::Circle},
        {3, 0.6f, Enemy::Type::Square},
        {2, 1.3f, Enemy::Type::Pentagon},
        {2, 0.7f, Enemy::Type::Circle}
    });
    
    m_waves.push_back({
        {2, 1.1f, Enemy::Type::Pentagon},
        {3, 0.6f, Enemy::Type::Triangle},
        {3, 0.7f, Enemy::Type::Circle},
        {4, 0.5f, Enemy::Type::Square},
        {2, 1.1f, Enemy::Type::Pentagon},
        {2, 0.6f, Enemy::Type::Circle}
    });
}

void WaveManager::spawnEnemy(const WaveConfig& config)
{
    static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    
    constexpr float WINDOW_WIDTH = 800.f;
    constexpr float WINDOW_HEIGHT = 600.f;
    constexpr float SPAWN_OFFSET = 50.f;
    
    std::uniform_int_distribution<int> sideDist(0, 3);
    int side = sideDist(rng);
    
    float spawnX = 0.f;
    float spawnY = 0.f;
    
    switch (side)
    {
    case 0:
        spawnX = std::uniform_real_distribution<float>(SPAWN_OFFSET, WINDOW_WIDTH - SPAWN_OFFSET)(rng);
        spawnY = -SPAWN_OFFSET;
        break;
    case 1:
        spawnX = WINDOW_WIDTH + SPAWN_OFFSET;
        spawnY = std::uniform_real_distribution<float>(SPAWN_OFFSET, WINDOW_HEIGHT - SPAWN_OFFSET)(rng);
        break;
    case 2:
        spawnX = std::uniform_real_distribution<float>(SPAWN_OFFSET, WINDOW_WIDTH - SPAWN_OFFSET)(rng);
        spawnY = WINDOW_HEIGHT + SPAWN_OFFSET;
        break;
    case 3:
        spawnX = -SPAWN_OFFSET;
        spawnY = std::uniform_real_distribution<float>(SPAWN_OFFSET, WINDOW_HEIGHT - SPAWN_OFFSET)(rng);
        break;
    }
    
    std::uniform_real_distribution<float> offsetDist(-20.f, 20.f);
    
    for (int i = 0; i < config.enemyCount; ++i)
    {
        float offsetX = offsetDist(rng);
        float offsetY = offsetDist(rng);
        
        auto enemy = std::make_unique<Enemy>(
            spawnX + offsetX,
            spawnY + offsetY,
            config.enemyType
        );
        m_enemies.push_back(std::move(enemy));
    }
}
