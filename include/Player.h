#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.h"
#include "Constants.h"

class Player {
    private: 
        sf::Texture bulletTexture, playerTexture;  // Texture stored as a member variable, safe not be killed out of scope
        sf::Sprite playerSprite;
        float speed;
        std::vector<Bullet> bullets;

        sf::Clock shootCooldownClock;   // Clock for shooting cooldown
        float shootCooldown;            // Cooldown duration in seconds



    public:
        Player(const sf::Vector2f& position, float speed, 
               const sf::Texture& playerTexture, const sf::Texture&  bulletTexture);
        void update(const sf::Vector2f& offset, float deltaTime);
        void draw(sf::RenderWindow& window) const;
        void shoot();
        std::vector<Bullet>& getBullets();
        sf::FloatRect getBounds() const;
        void resetPosition(sf::Vector2f psotion);

};

#endif // !PLAYER_H
