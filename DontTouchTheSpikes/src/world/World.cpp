#include "world/World.h"

World::World(const ContentLoader& content)
    : content(content),
    player(content.getTexture(TextureId::PlayerUp),
             content.getTexture(TextureId::PlayerDown),
             content.getTexture(TextureId::PlayerDead),
             content.getSfx(SfxId::Jump),
             content.getSfx(SfxId::Death),
             sf::Vector2f{WORLD_WIDTH / 2.0f, WORLD_HEIGHT / 2.0f}),
    backgroundSpikes(content.getTexture(TextureId::BackgroundSpikes)), backgroundScore(content.getTexture(TextureId::BackgroundScore)),
    scoreText(content.getFont(FontId::Score)),
    pointSound(content.getSfx(SfxId::Point))
{
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
    scoreText.setPosition({WORLD_WIDTH / 2.0f, WORLD_HEIGHT / 2.0f});

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

        if (!player.isPlayerDead())
        {
            generateSpikes(SpikeSide::Left);
            score++;
            scoreText.setString(getScoreText());
            setScoreColors();
            pointSound.play();
        }
    }

    handleSpikeCollision();

    const bool touchedTopSpikes = playerBounds.position.y <= TOP_SPIKES_HEIGHT;
    const bool touchedBottomSpikes = playerBounds.position.y + playerBounds.size.y >= WORLD_HEIGHT - BOTTOM_SPIKES_HEIGHT;

    if (touchedTopSpikes && player.getVelocityY() < 0.0f)
    {
        if (!player.isPlayerDead())
            player.die();

        std::uniform_real_distribution<float> dist(-6.0f, 6.0f);
        player.bounceVertical(dist(rng), -1.0f);
    }

    if (touchedBottomSpikes && player.getVelocityY() > 0.0f)
    {
        if (!player.isPlayerDead())
            player.die();

        std::uniform_real_distribution<float> dist(-6.0f, 6.0f);
        player.bounceVertical(dist(rng), 1.0f);
    }
}

void World::draw(sf::RenderTarget& target) const
{
    target.draw(backgroundSpikes);
    target.draw(backgroundScore);
    target.draw(scoreText);
    target.draw(player);

    for (auto& spike : spikes)
        target.draw(spike);
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

    for (auto& spike: spikes)
        spike.setSpikeColor(scheme.spikes);
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

void World::generateSpikes(SpikeSide side)
{
    spikes.push_back(Spike(content.getTexture(TextureId::Spike), {100.0f, 200.0f}, SpikeSide::Left));
    spikes.push_back(Spike(content.getTexture(TextureId::Spike), {200.0f, 200.0f}, SpikeSide::Right));
}

void World::handleSpikeCollision()
{
    for (auto& spike: spikes)
    {
        auto spikeBounds = spike.getBounds();
        auto playerBounds = player.getBounds();

        if (spikeBounds.findIntersection(playerBounds))
        {
            player.die();
            std::uniform_real_distribution<float> dist(-6.0f, 6.0f);
            player.bounceHorizontal(dist(rng));
        }
    }
}

sf::Color World::getBackgroundColor() const
{
    return backgroundColor;
}
