#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
#include <random>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class Game {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;
    sf::Text titleText;
    sf::Clock clock;
    sf::Clock enemySpawnClock;
    
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Bullet>> playerBullets;
    std::vector<std::unique_ptr<Bullet>> enemyBullets;
    
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<float> enemySpawnDist;
    
    int score;
    bool gameRunning;
    bool gameOver;
    bool showMenu;
    
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;
    static const float ENEMY_SPAWN_TIME;
    
public:
    Game();
    ~Game();
    
    void run();
    
private:
    void handleEvents();
    void update(float deltaTime);
    void render();
    void reset();
    void spawnEnemy();
    void checkCollisions();
    void updateScore();
    void loadFont();
};