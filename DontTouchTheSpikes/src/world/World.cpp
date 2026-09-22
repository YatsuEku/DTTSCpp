#include "world/World.h"

World::World(const ContentLoader& content)
    : content(content),
    player(content.getTexture(TextureId::PlayerUp),
             content.getTexture(TextureId::PlayerDown),
             sf::Vector2f{WORLD_WIDTH / 2 - 31, WORLD_HEIGHT / 2 - 20}),
    backgroundSpikes(content.getTexture(TextureId::BackgroundSpikes)), backgroundScore(content.getTexture(TextureId::BackgroundScore)),
    scoreText(content.getFont(FontId::Menu)) {
    sf::Vector2f backgroundCenter = backgroundSpikes.getLocalBounds().getCenter();
    backgroundSpikes.setOrigin(backgroundCenter);
    backgroundSpikes.setPosition({WORLD_WIDTH / 2.0f, WORLD_HEIGHT / 2.0f});

    sf::Vector2f scoreCenter = backgroundScore.getLocalBounds().getCenter();
    backgroundScore.setScale({0.65f, 0.65f});
    backgroundScore.setOrigin(scoreCenter);
    backgroundScore.setPosition({WORLD_WIDTH / 2.0f, WORLD_HEIGHT / 2.0f});

    scoreText.setString(std::to_string(score));
    sf::Vector2f scoreTextCenter = scoreText.getLocalBounds().getCenter();
    scoreText.setCharacterSize(32);
    scoreText.setOrigin(scoreTextCenter);
    scoreText.setPosition({WORLD_WIDTH / 2, WORLD_HEIGHT / 2});

    setScoreColors();
}

void World::update(float deltaTime)
{
    player.update(deltaTime);
}

void World::draw(sf::RenderTarget& target) const
{
    target.draw(backgroundSpikes);
    target.draw(backgroundScore);
    target.draw(scoreText);
    target.draw(player);
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

void World::setScoreColors()
{
    const auto& scheme = getBackgroundColorScheme(score);
    backgroundSpikes.setColor(scheme.spikes);
    backgroundColor = scheme.background;
    scoreText.setFillColor(scheme.background);
}

sf::Color World::getBackgroundColor() const
{
    return backgroundColor;
}
