#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"


class Bullet {
private:

    sf::Texture bullettexture;
    sf::Sprite spriteBullet;       // Sprite for the bullet
    sf::Vector2f velocity;   // Velocity of the bullet
    bool markedForRemoval;   // Flag to mark the bullet for removal

    sf::SoundBuffer shootBuffer;   // Sound buffer for the shoot sound
    sf::Sound shootSound;          // Sound effect for shooting



public:
    Bullet(const sf::Vector2f& position, const sf::Vector2f& speed, 
        const sf::Texture& texture);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
    bool isOffScreen() const;
    void markForRemoval();
    bool isMarkedForRemoval() const;
};

#endif // BULLET_H

