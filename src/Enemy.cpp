#include "Enemy.h"

const float Enemy::SPEED = 100.0f;
const float Enemy::SHOOT_COOLDOWN = 1.5f;
const float Enemy::WIDTH = 30.0f;
const float Enemy::HEIGHT = 30.0f;

Enemy::Enemy(float x, float y, std::mt19937& generator) 
    : velocity(0, SPEED), gen(generator), shootChance(0.0f, 1.0f), alive(true) {
    
    shape.setSize(sf::Vector2f(WIDTH, HEIGHT));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x - WIDTH/2, y - HEIGHT/2);
}

void Enemy::update(float deltaTime) {
    if (!alive) return;
    
    sf::Vector2f position = shape.getPosition();
    position += velocity * deltaTime;
    shape.setPosition(position);
}

void Enemy::render(sf::RenderWindow& window) {
    if (alive) {
        window.draw(shape);
    }
}

sf::Vector2f Enemy::getPosition() const {
    return shape.getPosition();
}

sf::FloatRect Enemy::getBounds() const {
    return shape.getGlobalBounds();
}

bool Enemy::shouldShoot() {
    if (!alive || shootClock.getElapsedTime().asSeconds() < SHOOT_COOLDOWN) {
        return false;
    }
    
    return shootChance(gen) < 0.02f; // 2% chance per frame when cooldown is ready
}

void Enemy::resetShootClock() {
    shootClock.restart();
}

bool Enemy::isOffScreen() const {
    return shape.getPosition().y > 650; // Slightly below screen bottom
}

bool Enemy::isAlive() const {
    return alive;
}

void Enemy::destroy() {
    alive = false;
}