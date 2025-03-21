#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Constants.h"

class Game {
private:
    sf::RenderWindow window;
    sf::Sprite background1Sprite, background2Sprite;

    sf::Font font;
    int SCORE;
    bool gameOver;
    sf::Text gameOverText; 
    sf::Text scoreText;

    sf::SoundBuffer gameOverBuffer;   // Sound buffer for gameOver
    sf::Sound gameOverSound;          // Sound effect for gameOver

    Player player;
    std::vector<Enemy> enemies;
    sf::Clock enemySpawnClock;
    float scrollSpeed;
    float enemySpeed;

    // Store textures
    sf::Texture playerTexture;
    sf::Texture enemyTexture; // Add this
    sf::Texture backgroundTexture;
    sf::Texture bulletTexture;

    sf::Text playAgainText;
    sf::Text quitText;
    bool isMouseOverPlayAgain;
    bool isMouseOverQuit;

    void handleInput(float deltaTime);
    void update(float deltaTime);
    void render();
    void checkCollisionsBullet();
    void checkCollisionsEnemy();
    void resetGame();

public:
    Game(const sf::Texture& playerTexture, const sf::Texture& enemyTexture,
         const sf::Texture& backgroundTexture, const sf::Texture& bulletTexture);
    //Game();
    void run();
};

#endif // !GAME_H


