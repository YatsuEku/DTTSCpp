#include "world/World.h"

World::World(const ContentLoader& content)
    : content(content),
    player(content.getTexture(TextureId::PlayerUp),
             content.getTexture(TextureId::PlayerDown),
             sf::Vector2f{WORLD_WIDTH / 2.0f, WORLD_HEIGHT / 2.0f}),
    backgroundSpikes(content.getTexture(TextureId::BackgroundSpikes)), backgroundScore(content.getTexture(TextureId::BackgroundScore)),
    scoreText(content.getFont(FontId::Score)) {
    sf::Vector2f backgroundCenter = backgroundSpikes.getLocalBounds().getCenter();
    backgroundSpikes.setOrigin(backgroundCenter);
    backgroundSpikes.setPosition({WORLD_WIDTH / 2.0f, WORLD_HEIGHT / 2.0f});

    sf::Vector2f scoreCenter = backgroundScore.getLocalBounds().getCenter();
    backgroundScore.setScale({0.65f, 0.65f});
    backgroundScore.setOrigin(scoreCenter);
    backgroundScore.setPosition({WORLD_WIDTH / 2.0f, WORLD_HEIGHT / 2.0f});

    scoreText.setString(getScoreText());
    scoreText.setCharacterSize(168);
    sf::Vector2f scoreTextCenter = scoreText.getLocalBounds().getCenter();
    scoreText.setOrigin(scoreTextCenter);
    scoreText.setPosition({WORLD_WIDTH / 2, WORLD_HEIGHT / 2});

    setScoreColors();
}

void World::update(float deltaTime)
{
    player.update(deltaTime);

    const auto& playerBounds = player.getBounds();

    if (playerBounds.position.x + playerBounds.size.x >= WORLD_WIDTH ||
        playerBounds.position.x <= 0)
    {
        player.bounceHorizontal();
        score++;
        scoreText.setString(getScoreText());
    }
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

        case GameState::Playing:
            player.startPlaying();
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

std::string World::getScoreText() const
{
    std::string out;

    if (score < 10)
        out = "0" + std::to_string(score);
    else
        out = std::to_string(score);

    return out;
}

sf::Color World::getBackgroundColor() const
{
    return backgroundColor;
}
