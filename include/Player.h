#pragma once

#include <SFML/Graphics.hpp>

class Player {
private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    sf::Clock shootClock;
    
    static const float SPEED;
    static const float SHOOT_COOLDOWN;
    static const float WIDTH;
    static const float HEIGHT;
    
public:
    Player(float x, float y);
    
    void handleInput();
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    bool canShoot() const;
    void resetShootClock();
    
    bool isAlive() const;
    void destroy();
    
private:
    bool alive;
};