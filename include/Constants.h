// Constants.h
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <SFML/Graphics.hpp>


const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 800;
const float PLAYER_SPEED = 0.2f; // Player speed for the player
const float SCROLL_SPEED = 0.01f;   // Background scroll speed
const float ENEMY_SPEED = 0.05f;    // Enemy movement speed



// Texture paths
const std::string PLAYER_TEXTURE_PATH = "assets/figures/fighter1.png";
const std::string ENEMY_TEXTURE_PATH = "assets/figures/enemy1.png";
const std::string BACKGROUND_TEXTURE_PATH = "assets/figures/background1.png";
const std::string BULLET_TEXTURE_PATH = "assets/figures/bullet1.png";



#endif // CONSTANTS_H