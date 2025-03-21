#include "Enemy.h"

Enemy::Enemy(const sf::Vector2f& position, float speed, const sf::Texture& enemyTexture)
    : velocity(0.f, speed), spriteEnemy(enemyTexture), 
    markedForRemoval(false) {
    
        
        // Set the texture to the sprite
        spriteEnemy.setTexture(enemyTexture);
        //sf::FloatRect bounds = spriteEnemy.getLocalBounds();
        spriteEnemy.setTextureRect(sf::IntRect({0, 0}, {100, 98}));
        spriteEnemy.setScale({0.5f, 0.5f});

        sf::Vector2u spriteEnemySize = enemyTexture.getSize();
        //std::cout << "Texture size: " << enemyTexture.getSize().x << "x" << enemyTexture.getSize().y << std::endl;
        spriteEnemy.setOrigin({spriteEnemySize.x / 2.0f, spriteEnemySize.y / 2.0f});

        // Set the initial position
        spriteEnemy.setPosition(position);
}


void Enemy::update(float deltaTime) {
    spriteEnemy.move(velocity * deltaTime); // Move downward
}

void Enemy::draw(sf::RenderWindow& window) const {
    //std::cout << "Enemy position: (" << spriteEnemy.getPosition().x << ", " << spriteEnemy.getPosition().y << ")\n";
    window.draw(spriteEnemy);
}

sf::FloatRect Enemy::getBounds() const {
    return spriteEnemy.getGlobalBounds();
}

bool Enemy::isOffScreen() const {
    sf::Vector2f pos = spriteEnemy.getPosition();
    return pos.y > WINDOW_HEIGHT;
}

void Enemy::markForRemoval() {
    markedForRemoval = true;
}

bool Enemy::isMarkedForRemoval() const {
    return markedForRemoval;
}


