#include "Player.h"

const float Player::SPEED = 300.0f;
const float Player::SHOOT_COOLDOWN = 0.2f;
const float Player::WIDTH = 30.0f;
const float Player::HEIGHT = 40.0f;

Player::Player(float x, float y) : velocity(0, 0), alive(true) {
    shape.setSize(sf::Vector2f(WIDTH, HEIGHT));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(x - WIDTH/2, y - HEIGHT/2);
}

void Player::handleInput() {
    velocity.x = 0;
    velocity.y = 0;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocity.x = -SPEED;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocity.x = SPEED;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        velocity.y = -SPEED;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        velocity.y = SPEED;
    }
}

void Player::update(float deltaTime) {
    if (!alive) return;
    
    sf::Vector2f position = shape.getPosition();
    position += velocity * deltaTime;
    
    // Keep player within screen bounds
    if (position.x < 0) position.x = 0;
    if (position.x > 800 - WIDTH) position.x = 800 - WIDTH;
    if (position.y < 0) position.y = 0;
    if (position.y > 600 - HEIGHT) position.y = 600 - HEIGHT;
    
    shape.setPosition(position);
}

void Player::render(sf::RenderWindow& window) {
    if (alive) {
        window.draw(shape);
    }
}

sf::Vector2f Player::getPosition() const {
    return shape.getPosition();
}

sf::FloatRect Player::getBounds() const {
    return shape.getGlobalBounds();
}

bool Player::canShoot() const {
    return alive && shootClock.getElapsedTime().asSeconds() >= SHOOT_COOLDOWN;
}

void Player::resetShootClock() {
    shootClock.restart();
}

bool Player::isAlive() const {
    return alive;
}

void Player::destroy() {
    alive = false;
}