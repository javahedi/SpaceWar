#include "Game.h"


Game::Game(const sf::Texture& playerTexture, const sf::Texture& enemyTexture,
            const sf::Texture& backgroundTexture, const sf::Texture& bulletTexture,
            const sf::Texture& bossTexture, const sf::Texture& bulletBossTexture)
    : SCORE(0), 
      POWER_BOSS(20), 
      gameOver(false), 
      gameOverText(font, ""), 
      scoreText(font, ""),

      window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Space War"),
      player({WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 1.5f}, 
             PLAYER_SPEED, playerTexture, bulletTexture),
      
      //boss({WINDOW_WIDTH / 2.0f, 10.f }, bossTexture, bulletBossTexture),
      boss(nullptr),  // Initialize as nullptr
      nextBossSpawnScore(BOSS_ACTIVATION_SCORE),
      bossRespawnCooldown(10.0f),  // 10 seconds cooldown
      bossTexture(bossTexture),              // Store textures
      bulletBossTexture(bulletBossTexture), 

      scrollSpeed(SCROLL_SPEED), 
      enemySpeed(ENEMY_SPEED),
      isMouseOverPlayAgain(false), 
      isMouseOverQuit(false),
      playAgainText(font, "Play Again"), 
      quitText(font, "Quit"),
     
      enemyTexture(enemyTexture),           // Store enemy texture
      backgroundTexture(backgroundTexture),
      background1Sprite(backgroundTexture), 
      background2Sprite(backgroundTexture),
      gameOverBuffer(), 
      gameOverSound(gameOverBuffer), 
      explosionBuffer(),
      explosionSound(explosionBuffer)
    {

        // Initialize background sprites
        background1Sprite.setTexture(backgroundTexture);
        background2Sprite.setTexture(backgroundTexture);
        background1Sprite.setTextureRect(sf::IntRect({0, 0}, {WINDOW_WIDTH, WINDOW_HEIGHT}));
        background2Sprite.setTextureRect(sf::IntRect({0, 0}, {WINDOW_WIDTH, WINDOW_HEIGHT}));
        background1Sprite.setPosition({0.f, 0.f});
        background2Sprite.setPosition({0.f, -WINDOW_HEIGHT});


        // Load font
        if (!font.openFromFile("assets/fonts/arial.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
            exit(-1);
        }
        
        // Set up game over text
        gameOverText.setFont(font);
        gameOverText.setString("GAME OVER");
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setStyle(sf::Text::Bold);
        gameOverText.setPosition({WINDOW_WIDTH / 8.0f, WINDOW_HEIGHT / 4.0f});


        // Set up score text
        scoreText.setFont(font);
        scoreText.setCharacterSize(30);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition({10, WINDOW_HEIGHT - 40});


        playAgainText.setFont(font);
        playAgainText.setCharacterSize(30);
        playAgainText.setFillColor(sf::Color::White);
        playAgainText.setPosition({WINDOW_WIDTH / 2.0f -70, WINDOW_HEIGHT / 2.0f });

        quitText.setFont(font);
        quitText.setCharacterSize(30);
        quitText.setFillColor(sf::Color::White);
        quitText.setPosition({WINDOW_WIDTH / 2.0f -30, WINDOW_HEIGHT / 2.0f + 50});


        //shootBuffer("musics/sound.wav"); // Throws sf::Exception if an error occurs
        if (!gameOverBuffer.loadFromFile("assets/musics/gameOver.mp3")) {
            throw std::runtime_error("Failed to load hit sound effect!");
        }
        gameOverSound.setBuffer(gameOverBuffer);

        if (!explosionBuffer.loadFromFile("assets/musics/explosion-01.wav")) {
            throw std::runtime_error("Failed to load explosion sound effect!");
        }

        explosionSound.setBuffer(explosionBuffer);
        

};


void Game::handleInput(float deltaTime) {
    // check all the window's events that were triggered since the last iteration of the loop
    while (const std::optional event = window.pollEvent())
    {
        // "close requested" event: we close the window
        if (event->is<sf::Event::Closed>())
            window.close();
    }

    if (gameOver && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) ) {

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        // Check if "Play Again" button is clicked
        if (playAgainText.getGlobalBounds().contains(mousePos)) {
            resetGame(); // Reset the game
        }

        // Check if "Quit" button is clicked
        if (quitText.getGlobalBounds().contains(mousePos)) {
            window.close(); // Close the game
        }
    }

    if (!gameOver) {
        // Player movement
        sf::Vector2f direction(0, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) )  direction.x = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))  direction.x =  1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)   )  direction.y = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) )  direction.y =  1;

        // Normalize direction vector
        if (direction.x != 0 || direction.y != 0) {
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            direction /= length;
        }

        // Update player movement
        player.update(direction, deltaTime * 1.5f);


        // Shooting
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            player.shoot();
        }

    }
     

};


void Game::update(float deltaTime) {

    if (gameOver) {

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        isMouseOverPlayAgain = playAgainText.getGlobalBounds().contains(mousePos);
        isMouseOverQuit = quitText.getGlobalBounds().contains(mousePos);

        playAgainText.setFillColor(isMouseOverPlayAgain ? sf::Color::Yellow : sf::Color::White);
        quitText.setFillColor(isMouseOverQuit ? sf::Color::Yellow : sf::Color::White);

    } else
     {
        // Scroll background
        background1Sprite.move({0.f, SCROLL_SPEED * deltaTime});
        background2Sprite.move({0.f, SCROLL_SPEED * deltaTime});

        // Reset background position foe seamless scrolling
        if (background1Sprite.getPosition().y >= WINDOW_HEIGHT) {
            background1Sprite.setPosition({0.f, -WINDOW_HEIGHT});
        }

        if (background2Sprite.getPosition().y >= WINDOW_HEIGHT) {
            background2Sprite.setPosition({0.f, -WINDOW_HEIGHT});
        }

        // Spawn enemies
        if (enemySpawnClock.getElapsedTime().asSeconds() > 1.0f) {
            enemies.emplace_back(Enemy({static_cast<float>(rand() % WINDOW_WIDTH), -50.f}, ENEMY_SPEED, enemyTexture));
            enemySpawnClock.restart();
        }

        for (auto& enemy : enemies){
            enemy.update(deltaTime);
        }

        // Remove off-screen enemies
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), 
            [](const Enemy& enemy) {return enemy.isOffScreen(); }), enemies.end());

        checkCollisionsEnemy();
        checkCollisionsBullet();



        // Boss logic - checks both score and cooldown
        if (!bossActive && 
            SCORE >= nextBossSpawnScore && 
            bossRespawnClock.getElapsedTime().asSeconds() >= bossRespawnCooldown) 
        {
            spawnBoss();
        }
        
        if (boss && bossActive) {  // Always check before using
            boss->update(deltaTime);
            boss->shoot();
            checkCollisionsBoss();
            checkCollisionsBossBullet();
        }

        
    }
    
};


void Game::spawnBoss() {
    boss = std::make_unique<Boss>(
        sf::Vector2f{WINDOW_WIDTH / 2.0f, 100.f},  // Position
        bossTexture,                              // Boss texture
        bulletBossTexture                         // Bullet texture
    );
    bossActive = true;
    POWER_BOSS = 20;  // Reset boss health
    
}


void Game::render() {
    // clear the window with black color
    window.clear(sf::Color::Black);
        
    // Draw background
    window.draw(background1Sprite);
    window.draw(background2Sprite);

    // Draw player
    player.draw(window);
    // Draw enemies
    for (const auto& enemy : enemies){
        enemy.draw(window);
    }

    // Draw Boss
    if (bossActive  && SCORE > BOSS_ACTIVATION_SCORE ) {
        boss->draw(window);
    }


    if (gameOver) {
        scoreText.setString("Score: " + std::to_string(SCORE));
        window.draw(gameOverText);
        window.draw(scoreText);
        window.draw(playAgainText);
        window.draw(quitText);
    }
   
    window.display();
};


void Game::checkCollisionsEnemy() {
    for (auto& enemy : enemies) {
        if (player.getBounds().findIntersection(enemy.getBounds()).has_value()) {
            gameOver = true; 
            gameOverSound.play();
            break;
        } 
    } 

};




void Game::checkCollisionsBullet() {
    // Check collision between bullets and enemies

    auto& playerBullets = player.getBullets();
    for (auto& bullet : playerBullets) {
        for (auto& enemy : enemies) {
            // Check for intersection using findIntersection
            if (bullet.getBounds().findIntersection(enemy.getBounds()).has_value()) {
                enemy.markForRemoval();
                bullet.markForRemoval();
                SCORE++;
                break; // Exit inner loop after collision
            }
        }

        // Check if boss exists and is active
        if (boss && bossActive) {
            if (bullet.getBounds().findIntersection(boss->getBounds()).has_value()) {
                POWER_BOSS--;
                std::cout << "POWER_BOSS = " << POWER_BOSS << std::endl;
                
                if (POWER_BOSS <= 0) {
                    explosionSound.play();
                    boss->getBullets().clear();
                    boss.reset();  // Completely remove the boss instance
                    bossActive = false;
                    POWER_BOSS = 20;  // Reset for next boss spawn
                    SCORE     += 50;  // Bonus points for defeating boss

                    // Set next spawn threshold and start cooldown
                    nextBossSpawnScore = SCORE + 10;  // Require 10 more points
                    bossRespawnClock.restart();
                }
                bullet.markForRemoval();
            }
        }
    }

    playerBullets.erase(std::remove_if(playerBullets.begin(), playerBullets.end(), 
        [](const Bullet& bullet) {return bullet.isMarkedForRemoval();}),
        playerBullets.end());

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), 
        [](const Enemy& enemy) {return enemy.isMarkedForRemoval();}),
        enemies.end());

}



void Game::checkCollisionsBoss() {
    if (player.getBounds().findIntersection(boss->getBounds()).has_value()) {
        gameOver = true; 
        gameOverSound.play();
    } 
    
};



void Game::checkCollisionsBossBullet() {
    // Check collision between bullets and enemies
    auto& bossbullets = boss->getBullets();
    //std::cout << bullets.size() << std::endl;
    for (auto& bullet : bossbullets) {
        // Check for intersection using findIntersection
        if (bullet.getBounds().findIntersection(player.getBounds()).has_value()) {
            bullet.markForRemoval();
            gameOver = true; 
            gameOverSound.play();
        }
    }

};



void Game::resetGame() {
    gameOver   = false;
    SCORE      = 0;

    // Reset player state
    player.resetPosition({WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 1.5f});
    player.getBullets().clear();

    // Reset enemy state
    enemies.clear();

    // Reset boss state
    if (boss) {
        boss->getBullets().clear();
    }
    boss.reset();
    bossActive = false;
    POWER_BOSS = 20;
    

    ///
    background1Sprite.setTexture(backgroundTexture);
    background2Sprite.setTexture(backgroundTexture);
    background1Sprite.setTextureRect(sf::IntRect({0, 0}, {WINDOW_WIDTH, WINDOW_HEIGHT}));
    background2Sprite.setTextureRect(sf::IntRect({0, 0}, {WINDOW_WIDTH, WINDOW_HEIGHT}));
    background1Sprite.setPosition({0.f, 0.f});
    background2Sprite.setPosition({0.f, -WINDOW_HEIGHT});

    gameOverSound.stop();

}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds() * 1000.f;
        //std::cout << "deltaTime : " << deltaTime << "\n";
        handleInput(deltaTime);
        if (!window.isOpen()) {
            break; // Exit the loop if the window is closed
        }
        update(deltaTime);
        render();
    }

};


