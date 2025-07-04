#pragma once

#include <SFML/Graphics.hpp>

enum class BulletType {
    PLAYER,
    ENEMY
};

class Bullet {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    BulletType type;
    
    static const float PLAYER_SPEED;
    static const float ENEMY_SPEED;
    static const float RADIUS;
    
public:
    Bullet(float x, float y, BulletType bulletType);
    
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    BulletType getType() const;
    
    bool isOffScreen() const;
    bool isAlive() const;
    void destroy();
    
private:
    bool alive;
};