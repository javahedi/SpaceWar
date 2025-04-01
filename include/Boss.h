#ifndef BOSS_H
#define BOSS_H


#include <SFML/Graphics.hpp>
#include <SFML/System/Angle.hpp>  
#include "Constants.h"
#include <vector>
#include "Bullet.h"

class Boss {
    private: 
        sf::Texture bulletBossTexture, bossTexture;  // Texture stored as a member variable, safe not be killed out of scope
        sf::Sprite bossSprite;
        std::vector<Bullet> bulletsBoss;
       
        sf::Clock movementChangeClock;  // Controls when boss changes movement
        float movementChangeInterval;   // How often movement changes (seconds)
        bool isDiving;                 // Is the boss diving toward the player?
        sf::Vector2f diveTarget;       // Target position when diving
        float diveSpeed;               // Speed when diving
        float horizontalSpeed;         // Speed for left/right movement
        bool isReturningUp;          // Is boss returning upward?
        sf::Vector2f returnTarget;   // Target position when returning up


        sf::Clock shootCooldownClock;   // Clock for shooting cooldown
        float shootCooldown;            // Cooldown duration in seconds
        int bulletStreams;       // Number of bullet streams (3 or 5)
        float shootAngleStep;    // Angle between bullet streams (in radians)
        float baseShootCooldown; // Base cooldown (adjustable)

    public:
        Boss(const sf::Vector2f& position, 
             const sf::Texture& bossTexture, const sf::Texture& bulletBossTexture);
        
        void update(float deltaTime);
        void draw(sf::RenderWindow& window) const;
        void shoot();
        std::vector<Bullet>& getBullets();
        sf::FloatRect getBounds() const;
        void resetPosition(sf::Vector2f position);
       
};


#endif // !BOSS_H