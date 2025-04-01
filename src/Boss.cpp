#include "Boss.h"


Boss::Boss(const sf::Vector2f& position,
           const sf::Texture& bossTexture, 
           const sf::Texture& bulletBossTexture)
        : 
          shootCooldown(3.f),       // Default: 1 second cooldown
          baseShootCooldown(3.f),  // Same as shootCooldown (adjustable)
          bulletStreams(3),         // Default: 3-way spread
          shootAngleStep(45.f * (3.14159f / 180.f)),  // Convert 45° to radians
          bossTexture(bossTexture),
          bulletBossTexture(bulletBossTexture), 
          bossSprite(bossTexture),
          movementChangeInterval(0.2f), 
          isDiving(false), 
          diveSpeed(0.1f), 
          horizontalSpeed(0.1f) 
           {

            bossSprite.setTexture(bossTexture);
            bossSprite.setTextureRect(sf::IntRect({0,0},{200,200}));
            bossSprite.setScale({0.5f, 0.5f}); 
            sf::Vector2u bossSpriteSize = bossTexture.getSize();
            bossSprite.setOrigin({bossSpriteSize.x / 2.f, bossSpriteSize.y / 2.f});
            bossSprite.setRotation(sf::degrees(180.f));  // Proper SFML 3.0 way
            bossSprite.setPosition(position);
        }



void Boss::update(float deltaTime) {
    // 1. Handle Boss Movement
    if (movementChangeClock.getElapsedTime().asSeconds() > movementChangeInterval) {
        movementChangeClock.restart();
        
        // Randomly decide next action
        int action = rand() % 4; // 0=Stay, 1=Move left/right, 2=Dive, 3=Return up
        
        if (action == 0) {
            // Stay centered
            isDiving = false;
            isReturningUp = false;
            horizontalSpeed = 0;
        } 
        else if (action == 1) {
            // Move left or right randomly
            isDiving = false;
            isReturningUp = false;
            horizontalSpeed = (rand() % 2 == 0) ? 1.f : -1.f;
        } 
        else if (action == 2) {
            // Dive toward middle-bottom
            isDiving = true;
            isReturningUp = false;
            diveTarget = sf::Vector2f(
                WINDOW_WIDTH/2.f,  // Center X
                WINDOW_HEIGHT * 0.7f  // 70% down screen
            );
        }
        else if (action == 3 && !isDiving) {
            // Return upward (only if not already diving)
            isReturningUp = true;
            returnTarget = sf::Vector2f(
                bossSprite.getPosition().x, 
                WINDOW_HEIGHT * 0.2f  // 20% from top
            );
        }
    }

    // 2. Apply Movement
    sf::Vector2f movement(0, SCROLL_SPEED * deltaTime); // Background scroll
    
    if (isDiving) {
        // Move toward dive target
        sf::Vector2f direction = diveTarget - bossSprite.getPosition();
        float distance = std::sqrt(direction.x*direction.x + direction.y*direction.y);
        
        if (distance > 5.f) {
            direction /= distance; // Normalize
            movement += direction * diveSpeed * deltaTime;
        } else {
            isDiving = false;
            // 30% chance to return up after dive
            if (rand() % 100 < 30) {
                isReturningUp = true;
                returnTarget = sf::Vector2f(
                    bossSprite.getPosition().x,
                    WINDOW_HEIGHT * 0.2f
                );
            }
        }
    } 
    else if (isReturningUp) {
        // Move toward return target
        sf::Vector2f direction = returnTarget - bossSprite.getPosition();
        float distance = std::sqrt(direction.x*direction.x + direction.y*direction.y);
        
        if (distance > 5.f) {
            direction /= distance;
            movement += direction * diveSpeed * deltaTime;
        } else {
            isReturningUp = false;
        }
    }
    else {
        // Normal horizontal movement
        movement.x = horizontalSpeed * deltaTime;
    }

    bossSprite.move(movement);

    // 3. Enforce screen boundaries
    sf::Vector2f pos = bossSprite.getPosition();    
    if (pos.x < 0            ) bossSprite.setPosition({0, pos.y});
    if (pos.y < 0            ) bossSprite.setPosition({pos.x, 0});
    if (pos.x > WINDOW_WIDTH ) bossSprite.setPosition({WINDOW_WIDTH, pos.y});
    if (pos.y > WINDOW_HEIGHT) bossSprite.setPosition({pos.x, WINDOW_HEIGHT});


    // 4. Update bullets
    for (auto& bullet : bulletsBoss) {
        bullet.update(deltaTime);
    }
    bulletsBoss.erase(std::remove_if(bulletsBoss.begin(), bulletsBoss.end(),
        [](const Bullet& bullet) { return bullet.isOffScreen(); }), bulletsBoss.end());
}


void Boss::shoot() {
    if (shootCooldownClock.getElapsedTime().asSeconds() >= shootCooldown) {
        sf::Vector2f bulletPosition = bossSprite.getPosition();
        
        // Central bullet (always shoots downward)
        bulletsBoss.emplace_back(bulletPosition, sf::Vector2f(0, 1), bulletBossTexture);
        
        // Radial bullets (left and right streams)
        for (int i = 1; i <= bulletStreams / 2; ++i) {
            float angle = shootAngleStep * i;
            
            // Left-side bullet
            bulletsBoss.emplace_back(
                bulletPosition,
                sf::Vector2f(-sin(angle), cos(angle)), // Direction vector
                bulletBossTexture
            );
            
            // Right-side bullet
            bulletsBoss.emplace_back(
                bulletPosition,
                sf::Vector2f(sin(angle), cos(angle)), // Direction vector
                bulletBossTexture
            );
        }
        shootCooldownClock.restart();
    }
}



void Boss::draw(sf::RenderWindow& window) const {
    window.draw(bossSprite);
    for (const auto& bullet : bulletsBoss) {
         bullet.draw(window);
     }
 }


std::vector<Bullet>& Boss::getBullets() {
    return bulletsBoss;
}


sf::FloatRect Boss::getBounds() const {
    return bossSprite.getGlobalBounds();
}

void Boss::resetPosition(sf::Vector2f position) {
    bossSprite.setPosition(position);
}
