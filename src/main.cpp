
#include "Game.h"
#include "Constants.h"
#include <iostream>

bool loadTextures(sf::Texture& playerTexture, sf::Texture& enemyTexture, 
                  sf::Texture& backgroundTexture, sf::Texture& bulletTexture,
                  sf::Texture& bossTexture, sf::Texture& bulletBossTexture) {
    if (!playerTexture.loadFromFile(TexturePaths::PLAYER_TEXTURE_PATH)) {
        std::cerr << "Failed to load player texture!" << std::endl;
        return false;
    }
    if (!enemyTexture.loadFromFile( TexturePaths::ENEMY_TEXTURE_PATH)) {
        std::cerr << "Failed to load enemy texture!" << std::endl;
        return false;
    }
    if (!backgroundTexture.loadFromFile(TexturePaths::BACKGROUND_TEXTURE_PATH)) {
        std::cerr << "Failed to load background texture!" << std::endl;
        return false;
    }
    if (!bulletTexture.loadFromFile(TexturePaths::BULLET_TEXTURE_PATH)) {
        std::cerr << "Failed to load bullet texture!" << std::endl;
        return false;
    }

    if (!bulletBossTexture.loadFromFile(TexturePaths::BOSS_BULLET_TEXTURE_PATH)) {
        std::cerr << "Failed to load boss bullet texture!" << std::endl;
        return false;
    }

    if (!bossTexture.loadFromFile(TexturePaths::BOSS_TEXTURE_PATH)) {
        std::cerr << "Failed to load boss texture!" << std::endl;
        return false;
    }



    return true;
}


int main() {
    sf::Texture playerTexture, enemyTexture, backgroundTexture, 
                bulletTexture, bossTexture, bulletBossTexture;

    if (!loadTextures(playerTexture, enemyTexture, 
                        backgroundTexture, bulletTexture,
                        bossTexture, bulletBossTexture)) {
        return -1; // Exit if textures fail to load
    }

    try { 
        
        Game game(playerTexture, enemyTexture, 
              backgroundTexture, bulletTexture,
              bossTexture, bulletBossTexture);
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "An exception occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
