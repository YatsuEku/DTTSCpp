#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ContentLoader.h"
#include "core/GameState.h"

const int WORLD_WIDTH = 540;
const int WORLD_HEIGHT = 960;

class World
{
public:
    explicit World(const ContentLoader& content);

    void draw(sf::RenderTarget& target) const;
    void update(float deltaTime);
    void onGameStateChanged(GameState newState);

private:
    ContentLoader content;
    Player player;
    sf::Sprite backgroundSpikes;
};
