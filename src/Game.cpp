#include "Game.h"
#include <iostream>

const float Game::ENEMY_SPAWN_TIME = 2.0f;

Game::Game() 
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Shooter", sf::Style::Close)
    , gen(rd())
    , enemySpawnDist(50.0f, WINDOW_WIDTH - 50.0f)
    , score(0)
    , gameRunning(false)
    , gameOver(false)
    , showMenu(true) {
    
    window.setFramerateLimit(60);
    loadFont();
    
    // Initialize texts
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);
    
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER\nPress R to restart\nPress ESC to quit");
    sf::FloatRect gameOverBounds = gameOverText.getLocalBounds();
    gameOverText.setPosition(
        (WINDOW_WIDTH - gameOverBounds.width) / 2,
        (WINDOW_HEIGHT - gameOverBounds.height) / 2
    );
    
    titleText.setFont(font);
    titleText.setCharacterSize(36);
    titleText.setFillColor(sf::Color::Cyan);
    titleText.setString("SPACE SHOOTER\n\nPress SPACE to start\nUse WASD/Arrow keys to move\nPress SPACE to shoot\nPress ESC to quit");
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setPosition(
        (WINDOW_WIDTH - titleBounds.width) / 2,
        (WINDOW_HEIGHT - titleBounds.height) / 2
    );
    
    player = std::make_unique<Player>(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50);
}

Game::~Game() = default;

void Game::loadFont() {
    // Create a simple built-in font fallback
    if (!font.loadFromFile("assets/arial.ttf")) {
        // If we can't load a font file, we'll use the default font
        std::cout << "Warning: Could not load font file. Using default font." << std::endl;
    }
}

void Game::run() {
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        handleEvents();
        
        if (gameRunning && !gameOver) {
            update(deltaTime);
        }
        
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
                
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                else if (showMenu && event.key.code == sf::Keyboard::Space) {
                    showMenu = false;
                    gameRunning = true;
                    gameOver = false;
                    reset();
                }
                else if (gameOver && event.key.code == sf::Keyboard::R) {
                    gameOver = false;
                    gameRunning = true;
                    reset();
                }
                else if (gameRunning && !gameOver && event.key.code == sf::Keyboard::Space) {
                    if (player->canShoot()) {
                        sf::Vector2f playerPos = player->getPosition();
                        playerBullets.push_back(std::make_unique<Bullet>(
                            playerPos.x + 15, playerPos.y, BulletType::PLAYER));
                        player->resetShootClock();
                    }
                }
                break;
                
            default:
                break;
        }
    }
}

void Game::update(float deltaTime) {
    // Update player
    if (player->isAlive()) {
        player->handleInput();
        player->update(deltaTime);
    }
    
    // Spawn enemies
    if (enemySpawnClock.getElapsedTime().asSeconds() >= ENEMY_SPAWN_TIME) {
        spawnEnemy();
        enemySpawnClock.restart();
    }
    
    // Update enemies
    for (auto it = enemies.begin(); it != enemies.end();) {
        (*it)->update(deltaTime);
        
        if ((*it)->isOffScreen() || !(*it)->isAlive()) {
            it = enemies.erase(it);
        } else {
            // Enemy shooting
            if ((*it)->shouldShoot()) {
                sf::Vector2f enemyPos = (*it)->getPosition();
                enemyBullets.push_back(std::make_unique<Bullet>(
                    enemyPos.x + 15, enemyPos.y + 30, BulletType::ENEMY));
                (*it)->resetShootClock();
            }
            ++it;
        }
    }
    
    // Update player bullets
    for (auto it = playerBullets.begin(); it != playerBullets.end();) {
        (*it)->update(deltaTime);
        
        if ((*it)->isOffScreen() || !(*it)->isAlive()) {
            it = playerBullets.erase(it);
        } else {
            ++it;
        }
    }
    
    // Update enemy bullets
    for (auto it = enemyBullets.begin(); it != enemyBullets.end();) {
        (*it)->update(deltaTime);
        
        if ((*it)->isOffScreen() || !(*it)->isAlive()) {
            it = enemyBullets.erase(it);
        } else {
            ++it;
        }
    }
    
    checkCollisions();
    updateScore();
    
    // Check game over
    if (!player->isAlive()) {
        gameOver = true;
        gameRunning = false;
    }
}

void Game::render() {
    window.clear(sf::Color::Black);
    
    if (showMenu) {
        window.draw(titleText);
    }
    else if (gameOver) {
        window.draw(gameOverText);
    }
    else {
        // Render game objects
        if (player->isAlive()) {
            player->render(window);
        }
        
        for (const auto& enemy : enemies) {
            enemy->render(window);
        }
        
        for (const auto& bullet : playerBullets) {
            bullet->render(window);
        }
        
        for (const auto& bullet : enemyBullets) {
            bullet->render(window);
        }
        
        window.draw(scoreText);
    }
    
    window.display();
}

void Game::reset() {
    score = 0;
    enemies.clear();
    playerBullets.clear();
    enemyBullets.clear();
    player = std::make_unique<Player>(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50);
    enemySpawnClock.restart();
}

void Game::spawnEnemy() {
    float x = enemySpawnDist(gen);
    enemies.push_back(std::make_unique<Enemy>(x, -30, gen));
}

void Game::checkCollisions() {
    // Player bullets vs enemies
    for (auto bulletIt = playerBullets.begin(); bulletIt != playerBullets.end();) {
        bool bulletHit = false;
        
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
            if ((*bulletIt)->getBounds().intersects((*enemyIt)->getBounds())) {
                (*bulletIt)->destroy();
                (*enemyIt)->destroy();
                score += 10;
                bulletHit = true;
                break;
            }
            ++enemyIt;
        }
        
        if (bulletHit || (*bulletIt)->isOffScreen() || !(*bulletIt)->isAlive()) {
            bulletIt = playerBullets.erase(bulletIt);
        } else {
            ++bulletIt;
        }
    }
    
    // Enemy bullets vs player
    for (auto bulletIt = enemyBullets.begin(); bulletIt != enemyBullets.end();) {
        if (player->isAlive() && (*bulletIt)->getBounds().intersects(player->getBounds())) {
            (*bulletIt)->destroy();
            player->destroy();
            bulletIt = enemyBullets.erase(bulletIt);
        } else {
            ++bulletIt;
        }
    }
    
    // Enemies vs player
    if (player->isAlive()) {
        for (const auto& enemy : enemies) {
            if (enemy->isAlive() && enemy->getBounds().intersects(player->getBounds())) {
                player->destroy();
                break;
            }
        }
    }
}

void Game::updateScore() {
    scoreText.setString("Score: " + std::to_string(score));
}