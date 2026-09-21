#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ContentLoader.h"

class World
{
public:
    explicit World(const ContentLoader& content);

    void draw(sf::RenderTarget& target) const;
    void update(float deltaTime);

private:
    ContentLoader content;
    Player player;
};
