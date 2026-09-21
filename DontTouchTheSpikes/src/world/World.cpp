#include "world/World.h"

World::World()
    : player()
{
}

void World::update(float deltaTime)
{
    player.update(deltaTime);
}

void World::draw(sf::RenderTarget& target) const
{
    target.draw(player);
}