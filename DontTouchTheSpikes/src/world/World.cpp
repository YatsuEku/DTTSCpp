#include "world/World.h"

World::World(const ContentLoader& content)
    : content(content),
    player(content.getTexture(TextureId::Player), sf::Vector2f{100, 100})
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