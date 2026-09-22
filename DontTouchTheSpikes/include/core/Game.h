#pragma once

#include <SFML/Graphics.hpp>
#include "world/World.h"
#include "ContentLoader.h"
#include "core/GameState.h"

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

    void load();
    void draw();
    void update(float deltaTime);
    void setState(GameState newState);
};
