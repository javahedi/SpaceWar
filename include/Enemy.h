#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <iostream>

class Enemy {
private:
    sf::Sprite spriteEnemy;
    sf::Vector2f velocity;
    bool markedForRemoval;

public:
    Enemy(const sf::Vector2f& position, float speed, const sf::Texture& enemyTexture);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
    bool isOffScreen() const;
    void markForRemoval();
    bool isMarkedForRemoval() const;
};

#endif // ENEMY_H


