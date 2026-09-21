#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class World
{
public:
    World();

    void draw(sf::RenderTarget& target) const;
    void update(float deltaTime);

private:
    Player player;
};
