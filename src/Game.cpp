#include "Game.h"
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>

Game::Game()
    : m_window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "Space Defender")
    , m_score(0)
    , m_resources(STARTING_RESOURCES)
    , m_gameOver(false)
    , m_victory(false)
    , m_showPlacementPreview(false)
{
    // Инициализация базы в центре экрана
    m_base = std::make_unique<Base>(WINDOW_WIDTH / 2.f - 30.f, WINDOW_HEIGHT / 2.f - 30.f);
    
    // Инициализация защитников
    initializeDefenders();
    
    // Инициализация шрифта (используем системный шрифт)
    // Пытаемся загрузить шрифт, если не получается - используем дефолтный
    #ifdef _WIN32
    if (!m_font.openFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        // Если не удалось загрузить, используем дефолтный шрифт
        // В реальном проекте можно использовать встроенные ресурсы
    }
    #else
    // Для других платформ можно указать другие пути
    #endif
    
    // Настройка UI текста (создаем после загрузки шрифта)
    m_scoreText = std::make_unique<sf::Text>(m_font, "", 24);
    m_scoreText->setFillColor(sf::Color::White);
    m_scoreText->setPosition(sf::Vector2f(10.f, 10.f));
    
    m_healthText = std::make_unique<sf::Text>(m_font, "", 24);
    m_healthText->setFillColor(sf::Color::White);
    m_healthText->setPosition(sf::Vector2f(10.f, 40.f));
    
    m_waveText = std::make_unique<sf::Text>(m_font, "", 24);
    m_waveText->setFillColor(sf::Color::White);
    m_waveText->setPosition(sf::Vector2f(10.f, 70.f));
    
    m_gameOverText = std::make_unique<sf::Text>(m_font, "GAME OVER\nPress R to Restart", 48);
    m_gameOverText->setFillColor(sf::Color::Red);
    m_gameOverText->setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f - 150.f, WINDOW_HEIGHT / 2.f - 50.f));
    
    m_victoryText = std::make_unique<sf::Text>(m_font, "VICTORY!\nPress R to Restart", 48);
    m_victoryText->setFillColor(sf::Color::Green);
    m_victoryText->setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f - 120.f, WINDOW_HEIGHT / 2.f - 50.f));
    
    m_resourcesText = std::make_unique<sf::Text>(m_font, "", 24);
    m_resourcesText->setFillColor(sf::Color::Yellow);
    m_resourcesText->setPosition(sf::Vector2f(10.f, 100.f));
    
    m_instructionsText = std::make_unique<sf::Text>(m_font, "Click to place defenders (cost: 50)\nDefend the base! Enemies spawn from sides.\nSurvive all waves to win! Press R to restart.", 16);
    m_instructionsText->setFillColor(sf::Color::Cyan);
    m_instructionsText->setPosition(sf::Vector2f(10.f, static_cast<float>(WINDOW_HEIGHT - 70)));
    
    // Устанавливаем цель для врагов
    for (auto& enemy : *m_waveManager.getEnemies())
    {
        enemy->setTarget(m_base.get());
    }
}

void Game::run()
{
    while (m_window.isOpen())
    {
        float deltaTime = m_clock.restart().asSeconds();
        
        handleEvents();
        
        if (!m_gameOver && !m_victory)
        {
            update(deltaTime);
        }
        
        render();
    }
}

void Game::update(float deltaTime)
{
    updateWaveManager(deltaTime);
    updateDefenders(deltaTime);
    checkCollisions();
    updateUI();
    
    // Проверка условий победы/поражения
    if (m_base->isDestroyed())
    {
        m_gameOver = true;
    }
    else if (!m_waveManager.hasMoreWaves() && 
             !m_waveManager.isWaveActive() && 
             m_waveManager.getEnemies()->empty())
    {
        m_victory = true;
    }
}

void Game::handleEvents()
{
    while (const std::optional event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window.close();
        }
        
        if (event->is<sf::Event::MouseMoved>())
        {
            const auto& mouseEvent = event->getIf<sf::Event::MouseMoved>();
            if (mouseEvent)
            {
                m_mousePosition = sf::Vector2f(
                    static_cast<float>(mouseEvent->position.x),
                    static_cast<float>(mouseEvent->position.y)
                );
                m_showPlacementPreview = true;
            }
        }
        
        if (event->is<sf::Event::MouseButtonPressed>())
        {
            const auto& mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
            if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left)
            {
                if (!m_gameOver && !m_victory)
                {
                    placeDefender(m_mousePosition);
                }
            }
        }
        
        if (event->is<sf::Event::KeyPressed>())
        {
            const auto& keyEvent = event->getIf<sf::Event::KeyPressed>();
            if (keyEvent && keyEvent->code == sf::Keyboard::Key::R)
            {
                // Перезапуск игры
                m_score = 0;
                m_resources = STARTING_RESOURCES;
                m_gameOver = false;
                m_victory = false;
                m_base->reset();
                m_waveManager.reset();
                m_defenders.clear();
                
                for (auto& enemy : *m_waveManager.getEnemies())
                {
                    enemy->setTarget(m_base.get());
                }
            }
        }
    }
}

void Game::render()
{
    m_window.clear(BACKGROUND_COLOR);
    
    // Рисуем игровые объекты
    m_base->draw(m_window);
    
    // Рисуем предпросмотр размещения
    if (m_showPlacementPreview && !m_gameOver && !m_victory)
    {
        drawPlacementPreview();
    }
    
    for (const auto& defender : m_defenders)
    {
        defender->draw(m_window);
    }
    
    // Рисуем врагов
    for (const auto& enemy : *m_waveManager.getEnemies())
    {
        enemy->draw(m_window);
    }
    
    // Рисуем UI
    drawUI();
    
    if (m_gameOver)
    {
        drawGameOver();
    }
    else if (m_victory)
    {
        drawVictory();
    }
    
    m_window.display();
}

void Game::initializeDefenders()
{
    // Начальные защитники больше не создаются автоматически
    // Игрок должен размещать их сам
}

void Game::updateDefenders(float deltaTime)
{
    for (auto& defender : m_defenders)
    {
        defender->update(deltaTime);
    }
}

void Game::updateWaveManager(float deltaTime)
{
    // Автоматически запускаем следующую волну
    if (!m_waveManager.isWaveActive() && m_waveManager.hasMoreWaves())
    {
        m_waveManager.startNextWave();
    }
    
    m_waveManager.update(deltaTime);
    
    // Обновляем цель для всех врагов и обновляем их
    for (auto& enemy : *m_waveManager.getEnemies())
    {
        enemy->setTarget(m_base.get());
        enemy->update(deltaTime);
    }
}

void Game::checkCollisions()
{
    // Коллизии пуль с врагами
    for (auto& defender : m_defenders)
    {
        int resourcesEarned = CollisionManager::checkBulletEnemyCollisions(
            *defender->getBullets(),
            *m_waveManager.getEnemies(),
            m_score
        );
        
        // Начисляем ресурсы за убитых врагов
        m_resources += resourcesEarned;
    }
    
    // Коллизии врагов с базой
    CollisionManager::checkEnemyBaseCollisions(
        *m_waveManager.getEnemies(),
        *m_base
    );
}

void Game::updateUI()
{
    // Обновляем текст счета
    std::ostringstream scoreStream;
    scoreStream << "Score: " << m_score;
    m_scoreText->setString(scoreStream.str());
    
    // Обновляем текст здоровья
    std::ostringstream healthStream;
    healthStream << "Health: " << m_base->getHealth() << "/100";
    m_healthText->setString(healthStream.str());
    
    // Обновляем текст волны
    std::ostringstream waveStream;
    waveStream << "Wave: " << (m_waveManager.getCurrentWave() + 1) 
               << "/" << m_waveManager.getTotalWaves();
    m_waveText->setString(waveStream.str());
    
    // Обновляем текст ресурсов
    std::ostringstream resourcesStream;
    resourcesStream << "Resources: " << m_resources << " (Defender: " << DEFENDER_COST << ")";
    m_resourcesText->setString(resourcesStream.str());
}

void Game::drawUI()
{
    if (m_scoreText) m_window.draw(*m_scoreText);
    if (m_healthText) m_window.draw(*m_healthText);
    if (m_waveText) m_window.draw(*m_waveText);
    if (m_resourcesText) m_window.draw(*m_resourcesText);
    if (m_instructionsText) m_window.draw(*m_instructionsText);
}

void Game::drawGameOver()
{
    if (m_gameOverText) m_window.draw(*m_gameOverText);
}

void Game::drawVictory()
{
    if (m_victoryText) m_window.draw(*m_victoryText);
}

bool Game::canPlaceDefender(const sf::Vector2f& position) const
{
    // Проверяем, достаточно ли ресурсов
    if (m_resources < DEFENDER_COST)
        return false;
    
    // Проверяем, не слишком ли близко к базе
    sf::Vector2f basePos = m_base->getPosition();
    basePos.x += m_base->getBounds().size.x / 2.f;
    basePos.y += m_base->getBounds().size.y / 2.f;
    
    float distance = std::sqrt(
        (position.x - basePos.x) * (position.x - basePos.x) +
        (position.y - basePos.y) * (position.y - basePos.y)
    );
    
    if (distance < 80.f) // Минимальное расстояние от базы
        return false;
    
    // Проверяем, не пересекается ли с другими защитниками
    for (const auto& defender : m_defenders)
    {
        sf::Vector2f defenderPos = defender->getPosition();
        defenderPos.x += defender->getBounds().size.x / 2.f;
        defenderPos.y += defender->getBounds().size.y / 2.f;
        
        float dist = std::sqrt(
            (position.x - defenderPos.x) * (position.x - defenderPos.x) +
            (position.y - defenderPos.y) * (position.y - defenderPos.y)
        );
        
        if (dist < 40.f) // Минимальное расстояние между защитниками
            return false;
    }
    
    // Проверяем границы экрана
    if (position.x < 10.f || position.x > WINDOW_WIDTH - 10.f ||
        position.y < 10.f || position.y > WINDOW_HEIGHT - 10.f)
        return false;
    
    return true;
}

void Game::placeDefender(const sf::Vector2f& position)
{
    if (!canPlaceDefender(position))
        return;
    
    // Создаем защитника
    auto defender = std::make_unique<Defender>(position.x - 10.f, position.y - 10.f);
    defender->setEnemies(m_waveManager.getEnemies());
    m_defenders.push_back(std::move(defender));
    
    // Списываем ресурсы
    m_resources -= DEFENDER_COST;
}

void Game::drawPlacementPreview()
{
    sf::CircleShape preview(10.f);
    preview.setPosition(m_mousePosition - sf::Vector2f(10.f, 10.f));
    
    if (canPlaceDefender(m_mousePosition))
    {
        preview.setFillColor(sf::Color(0, 255, 0, 100)); // Зеленый, полупрозрачный
        preview.setOutlineColor(sf::Color::Green);
    }
    else
    {
        preview.setFillColor(sf::Color(255, 0, 0, 100)); // Красный, полупрозрачный
        preview.setOutlineColor(sf::Color::Red);
    }
    preview.setOutlineThickness(2.f);
    
    m_window.draw(preview);
}
