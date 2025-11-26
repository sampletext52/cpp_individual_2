#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include "Base.h"
#include "Defender.h"
#include "Enemy.h"
#include "WaveManager.h"
#include "CollisionManager.h"
#include "InputHandler.h"

class Game
{
public:
    Game();
    ~Game() = default;

    void run();

private:
    void handleEvents();
    void update(float deltaTime);
    void render();
    
    void initializeDefenders();
    void updateDefenders(float deltaTime);
    void updateWaveManager(float deltaTime);
    void checkCollisions();
    void updateUI();
    
    void drawUI();
    void drawGameOver();
    void drawVictory();
    void drawPlacementPreview();
    
    bool canPlaceDefender(const sf::Vector2f& position) const;
    void placeDefender(const sf::Vector2f& position);
    
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    sf::Font m_font;
    std::unique_ptr<sf::Text> m_scoreText;
    std::unique_ptr<sf::Text> m_healthText;
    std::unique_ptr<sf::Text> m_waveText;
    std::unique_ptr<sf::Text> m_resourcesText;
    std::unique_ptr<sf::Text> m_gameOverText;
    std::unique_ptr<sf::Text> m_victoryText;
    std::unique_ptr<sf::Text> m_instructionsText;
    
    std::unique_ptr<Base> m_base;
    std::vector<std::unique_ptr<Defender>> m_defenders;
    WaveManager m_waveManager;
    
    int m_score;
    int m_resources;
    bool m_gameOver;
    bool m_victory;
    sf::Vector2f m_mousePosition;
    bool m_showPlacementPreview;
    Enemy::Type m_selectedDefenderType;
    
    static constexpr int DEFENDER_COST = 40;
    static constexpr int STARTING_RESOURCES = 150;
    
    static constexpr int WINDOW_WIDTH = 800;
    static constexpr int WINDOW_HEIGHT = 600;
    static constexpr sf::Color BACKGROUND_COLOR = sf::Color(20, 20, 40);
};
