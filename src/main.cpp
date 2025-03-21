
#include "Game.h"
#include "Constants.h"
#include <iostream>

bool loadTextures(sf::Texture& playerTexture, sf::Texture& enemyTexture, 
                  sf::Texture& backgroundTexture, sf::Texture& bulletTexture) {
    if (!playerTexture.loadFromFile(PLAYER_TEXTURE_PATH)) {
        std::cerr << "Failed to load player texture!" << std::endl;
        return false;
    }
    if (!enemyTexture.loadFromFile(ENEMY_TEXTURE_PATH)) {
        std::cerr << "Failed to load enemy texture!" << std::endl;
        return false;
    }
    if (!backgroundTexture.loadFromFile(BACKGROUND_TEXTURE_PATH)) {
        std::cerr << "Failed to load background texture!" << std::endl;
        return false;
    }
    if (!bulletTexture.loadFromFile(BULLET_TEXTURE_PATH)) {
        std::cerr << "Failed to load bullet texture!" << std::endl;
        return false;
    }
    return true;
}


int main() {
    sf::Texture playerTexture, enemyTexture, backgroundTexture, bulletTexture;

    if (!loadTextures(playerTexture, enemyTexture, backgroundTexture, bulletTexture)) {
        return -1; // Exit if textures fail to load
    }

    try { 
        
        Game game(playerTexture, enemyTexture, backgroundTexture, bulletTexture);
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "An exception occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
