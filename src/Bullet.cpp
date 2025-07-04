#include "Bullet.h"

const float Bullet::PLAYER_SPEED = 500.0f;
const float Bullet::ENEMY_SPEED = 200.0f;
const float Bullet::RADIUS = 3.0f;

Bullet::Bullet(float x, float y, BulletType bulletType) : type(bulletType), alive(true) {
    shape.setRadius(RADIUS);
    shape.setPosition(x - RADIUS, y - RADIUS);
    
    if (type == BulletType::PLAYER) {
        velocity = sf::Vector2f(0, -PLAYER_SPEED);
        shape.setFillColor(sf::Color::Yellow);
    } else {
        velocity = sf::Vector2f(0, ENEMY_SPEED);
        shape.setFillColor(sf::Color::Magenta);
    }
}

void Bullet::update(float deltaTime) {
    if (!alive) return;
    
    sf::Vector2f position = shape.getPosition();
    position += velocity * deltaTime;
    shape.setPosition(position);
}

void Bullet::render(sf::RenderWindow& window) {
    if (alive) {
        window.draw(shape);
    }
}

sf::Vector2f Bullet::getPosition() const {
    return shape.getPosition();
}

sf::FloatRect Bullet::getBounds() const {
    return shape.getGlobalBounds();
}

BulletType Bullet::getType() const {
    return type;
}

bool Bullet::isOffScreen() const {
    sf::Vector2f pos = shape.getPosition();
    return pos.y < -10 || pos.y > 610;
}

bool Bullet::isAlive() const {
    return alive;
}

void Bullet::destroy() {
    alive = false;
}