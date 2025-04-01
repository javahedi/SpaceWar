#include "Player.h"



Player::Player(const sf::Vector2f& position, float speed, 
               const sf::Texture& playerTexture, 
               const sf::Texture& bulletTexture)
    : speed(speed), 
      shootCooldown(0.25f), 
      playerTexture(playerTexture),
      bulletTexture(bulletTexture), 
      playerSprite(playerTexture) {

        playerSprite.setTexture(playerTexture);
        playerSprite.setTextureRect(sf::IntRect({0, 0}, {100, 50}));
        sf::Vector2u playerSpriteSize = playerTexture.getSize();
        playerSprite.setOrigin({playerSpriteSize.x / 2.0f, playerSpriteSize.y / 2.0f});
        playerSprite.setPosition(position);

            
}
   

void Player::update(const sf::Vector2f& offset, float deltaTime) {
    playerSprite.move(offset * speed * deltaTime);

    // Boundary checks
    sf::Vector2f pos = playerSprite.getPosition();    
    if (pos.x < 0) playerSprite.setPosition({0, pos.y});
    if (pos.y < 0) playerSprite.setPosition({pos.x, 0});
    if (pos.x > WINDOW_WIDTH) playerSprite.setPosition({WINDOW_WIDTH, pos.y});
    if (pos.y > WINDOW_HEIGHT) playerSprite.setPosition({pos.x, WINDOW_HEIGHT});

    for (auto& bullet: bullets){
        bullet.update(deltaTime);
    }

    // Remove off-screen bullets
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](const Bullet& bullet) { return bullet.isOffScreen(); }), bullets.end());
}

void Player::draw(sf::RenderWindow& window) const {
   window.draw(playerSprite);
   for (const auto& bullet : bullets) {
        bullet.draw(window);
    }
}

void Player::shoot() {
    const int MAX_BULLETS = 3; 

    // Check if the cooldown has elapsed and the bullet limit is not exceeded
    if (shootCooldownClock.getElapsedTime().asSeconds() >= shootCooldown && bullets.size() < MAX_BULLETS) {
        // Spawn a new bullet
        sf::Vector2f bulletPosition = playerSprite.getPosition();
        bullets.emplace_back(bulletPosition, sf::Vector2f(0, -1), bulletTexture); // Bullet moves upward
        shootCooldownClock.restart();
    }
}


std::vector<Bullet>& Player::getBullets() {
    return bullets;
}

sf::FloatRect Player::getBounds() const {
    return playerSprite.getGlobalBounds();

}


void Player::resetPosition(sf::Vector2f postion) {
    playerSprite.setPosition(postion);
}