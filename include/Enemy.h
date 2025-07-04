#pragma once

#include <SFML/Graphics.hpp>
#include <random>

class Enemy {
private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    sf::Clock shootClock;
    
    static const float SPEED;
    static const float SHOOT_COOLDOWN;
    static const float WIDTH;
    static const float HEIGHT;
    
    std::mt19937& gen;
    std::uniform_real_distribution<float> shootChance;
    
public:
    Enemy(float x, float y, std::mt19937& generator);
    
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    bool shouldShoot();
    void resetShootClock();
    
    bool isOffScreen() const;
    bool isAlive() const;
    void destroy();
    
private:
    bool alive;
};