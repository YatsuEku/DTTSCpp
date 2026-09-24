#pragma once

#include <SFML/Graphics.hpp>
#include "world/World.h"
#include "ContentLoader.h"
#include "core/GameState.h"

constexpr std::string SAVE_FILE_NAME = "save.dat";
constexpr float FADE_IN_TEXT_DURATION = 1.5f;

class Game
{
public:
    Game();

    void init();
    void run();
private:
    ContentLoader content;
    World world;
    sf::RenderWindow window;
    GameState state;
    sf::Text scoreText;
    sf::Text highScoreText;
    sf::Text newHighScoreText;
    sf::Text tapToPlayText;
    int loadedHighScore;

    float gameOverTextAnimationTime;
    std::uint8_t alphaColor = 0;
    bool mousePressedLastFrame = false;

    void load();
    void draw();
    void update(float deltaTime);
    void setState(GameState newState);
    void onGameOver();
    void updateTextAnimation(float deltaTime);
    void saveGame();
    void loadGame();
    std::string getHighScoreString() const;
    std::string getScoreString() const;
};
