// Constants.h
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <SFML/Graphics.hpp>


// Use inline for C++17 to avoid multiple definition errors
inline const int WINDOW_WIDTH = 400;
inline const int WINDOW_HEIGHT = 800;
inline const float PLAYER_SPEED = 0.2f;
inline const float SCROLL_SPEED = 0.01f;
inline const float ENEMY_SPEED = 0.05f;
inline const int BOSS_ACTIVATION_SCORE = 5;  // Made const and inline

// For string constants, either make them static or use inline
namespace TexturePaths {
    inline const std::string PLAYER_TEXTURE_PATH      = "assets/figures/fighter1.png";
    inline const std::string ENEMY_TEXTURE_PATH       = "assets/figures/enemy1.png";
    inline const std::string BACKGROUND_TEXTURE_PATH  = "assets/figures/background1.png";
    inline const std::string BULLET_TEXTURE_PATH      = "assets/figures/bullet1.png";
    inline const std::string BOSS_TEXTURE_PATH        = "assets/figures/fighter3.png";
    inline const std::string BOSS_BULLET_TEXTURE_PATH = "assets/figures/bullet2.png";
}



#endif // CONSTANTS_H