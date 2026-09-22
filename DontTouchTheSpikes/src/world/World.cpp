#include "world/World.h"

World::World(const ContentLoader& content)
    : content(content),
    player(content.getTexture(TextureId::PlayerUp),
             content.getTexture(TextureId::PlayerDown),
             sf::Vector2f{WORLD_WIDTH / 2 - 31, WORLD_HEIGHT / 2 - 20}),
    backgroundSpikes(content.getTexture(TextureId::BackgroundSpikes))
{
}

void World::update(float deltaTime)
{
    player.update(deltaTime);
}

void World::draw(sf::RenderTarget& target) const
{
    target.draw(player);
    target.draw(backgroundSpikes);
}

void World::onGameStateChanged(GameState newState)
{
    switch(newState)
    {
    case GameState::Menu:
        player.playMenuAnimation();
        break;

    default:
        break;
    }
}