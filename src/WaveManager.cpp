#include "WaveManager.h"
#include <algorithm>

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
    if (!m_waveActive || m_currentWave > static_cast<int>(m_waves.size()))
        return;

    if (m_currentWave == 0 || m_currentWave > static_cast<int>(m_waves.size()))
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
    
    // Удаляем мертвых врагов
    m_enemies.erase(
        std::remove_if(m_enemies.begin(), m_enemies.end(),
            [](const std::unique_ptr<Enemy>& e) { return !e->isAlive(); }),
        m_enemies.end()
    );
    
    // Проверяем, закончилась ли волна
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
    // Волна 1: Квадраты
    m_waves.push_back({
        {5, 1.0f, Enemy::Type::Square},
        {5, 1.0f, Enemy::Type::Square},
        {3, 0.8f, Enemy::Type::Square}
    });
    
    // Волна 2: Квадраты и Треугольники
    m_waves.push_back({
        {3, 1.0f, Enemy::Type::Square},
        {3, 0.7f, Enemy::Type::Triangle},
        {2, 1.0f, Enemy::Type::Square},
        {2, 0.7f, Enemy::Type::Triangle}
    });
    
    // Волна 3: Все типы
    m_waves.push_back({
        {2, 1.5f, Enemy::Type::Pentagon},
        {3, 1.0f, Enemy::Type::Square},
        {2, 1.5f, Enemy::Type::Circle},
        {4, 0.6f, Enemy::Type::Triangle}
    });
    
    // Волна 4: Интенсивная смешанная
    m_waves.push_back({
        {5, 0.5f, Enemy::Type::Triangle},
        {3, 1.0f, Enemy::Type::Square},
        {3, 0.5f, Enemy::Type::Circle},
        {2, 1.5f, Enemy::Type::Pentagon},
        {4, 0.6f, Enemy::Type::Triangle}
    });
    
    // Волна 5: Финальная - все типы
    m_waves.push_back({
        {3, 1.0f, Enemy::Type::Pentagon},
        {5, 0.4f, Enemy::Type::Triangle},
        {3, 1.0f, Enemy::Type::Circle},
        {5, 0.4f, Enemy::Type::Square},
        {2, 1.5f, Enemy::Type::Pentagon}
    });
}

void WaveManager::spawnEnemy(const WaveConfig& config)
{
    // Спавним врагов с разных сторон экрана
    static int spawnCounter = 0;
    float spawnX = (spawnCounter % 2 == 0) ? -50.f : 850.f;
    float spawnY = 100.f + (spawnCounter % 3) * 150.f;
    spawnCounter++;
    
    for (int i = 0; i < config.enemyCount; ++i)
    {
        auto enemy = std::make_unique<Enemy>(
            spawnX + i * 40.f,
            spawnY,
            config.enemyType
        );
        m_enemies.push_back(std::move(enemy));
    }
}

