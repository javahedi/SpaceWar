#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "Player.h"
#include "Enemy.h"
#include "Constants.h"
#include "Boss.h"

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

    sf::SoundBuffer explosionBuffer;
    sf::Sound explosionSound;

    Player player;
    std::unique_ptr<Boss> boss;    
    bool bossActive = false;
    int POWER_BOSS;

    int nextBossSpawnScore;  // Score needed for next boss spawn
    float bossRespawnCooldown;  // Time delay before respawn
    sf::Clock bossRespawnClock;  // Timer for respawn delay

    
    std::vector<Enemy> enemies;
    sf::Clock enemySpawnClock;
    float scrollSpeed;
    float enemySpeed;

    // Store textures
    sf::Texture playerTexture;
    sf::Texture enemyTexture; // Add this
    sf::Texture backgroundTexture;
    sf::Texture bulletTexture;
    sf::Texture  bulletBossTexture, bossTexture;

    sf::Text playAgainText;
    sf::Text quitText;

    
    bool isMouseOverPlayAgain;
    bool isMouseOverQuit;

    void handleInput(float deltaTime);
    void update(float deltaTime);
    void render();
    void checkCollisionsBullet();
    void checkCollisionsEnemy();
    void checkCollisionsBoss();
    void checkCollisionsBossBullet();
    void resetGame();
    void spawnBoss();

public:
    Game(const sf::Texture& playerTexture, const sf::Texture& enemyTexture,
         const sf::Texture& backgroundTexture, const sf::Texture& bulletTexture,
         const sf::Texture& bossTexture, const sf::Texture& bulletBossTexture);
    void run();
};

#endif // !GAME_H


