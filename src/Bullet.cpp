#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& position, const sf::Vector2f& speed, 
                const sf::Texture& bullettexture)
        : velocity(speed), spriteBullet(bullettexture), markedForRemoval(false), 
        shootBuffer(), shootSound(shootBuffer) {
   
        // Set the texture to the sprite
        spriteBullet.setTexture(bullettexture);

        //sf::FloatRect bounds = spriteBullet.getLocalBounds();
        //spriteBullet.setTextureRect(sf::IntRect({0, 0}, {100, 50}));

        sf::Vector2u spriteBulletSize = bullettexture.getSize();
        spriteBullet.setOrigin({spriteBulletSize.x / 2.0f, spriteBulletSize.y / 2.0f});

        spriteBullet.setScale({0.8f, 0.6f});

        // Set the initial position
        spriteBullet.setPosition(position);


        //shootBuffer("musics/sound.wav"); // Throws sf::Exception if an error occurs
        if (!shootBuffer.loadFromFile("assets/musics/shoot.wav")) {
            throw std::runtime_error("Failed to load shoot sound effect!");
        }
    
        shootSound.setBuffer(shootBuffer);
        shootSound.play();



      
}

void Bullet::update(float deltaTime) {
    // Move the sprite based on velocity and deltaTime
    spriteBullet.move(velocity * deltaTime);
}

void Bullet::draw(sf::RenderWindow& window) const {
    // Draw the sprite to the window
    window.draw(spriteBullet);
}

sf::FloatRect Bullet::getBounds() const {
    // Return the global bounding box of the sprite
    return spriteBullet.getGlobalBounds();
}

bool Bullet::isOffScreen() const {
    // Check if the bullet is outside the window
    sf::Vector2f pos = spriteBullet.getPosition();
    return pos.x < 0 || pos.x > WINDOW_WIDTH || pos.y < 0 || pos.y > WINDOW_HEIGHT;
}

void Bullet::markForRemoval() {
    // Mark the bullet for removal
    markedForRemoval = true;
}

bool Bullet::isMarkedForRemoval() const {
    // Check if the bullet is marked for removal
    return markedForRemoval;
}


