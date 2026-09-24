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

    initializeSpikes();
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
            score++;
            scoreText.setString(getScoreText());
            setScoreColors();
            pointSound.play();

            currentSide = currentSide == SpikeSide::Right ? SpikeSide::Left : SpikeSide::Right;
            hideSpikes();
            showSpikes(currentSide);
        }
    }

    for (auto& spike: leftSpikes)
        spike.update(deltaTime);

    for (auto& spike: rightSpikes)
        spike.update(deltaTime);

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

    for (auto& spike : leftSpikes)
        target.draw(spike);

    for (auto& spike : rightSpikes)
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

void World::initializeSpikes()
{
    for (int i = 0; i < 13; i++)
    {
        Spike spike(content.getTexture(TextureId::Spike), {-19, i * 65.0f + TOP_SPIKES_HEIGHT + 35}, SpikeSide::Left);
        leftSpikes.push_back(spike);
    }

    for (int i = 0; i < 13; i++)
    {
        Spike spike(content.getTexture(TextureId::Spike), {WORLD_WIDTH + 19, i * 65.0f + TOP_SPIKES_HEIGHT + 35}, SpikeSide::Right);
        rightSpikes.push_back(spike);
    }
}

void World::setScoreColors()
{
    const auto& scheme = getBackgroundColorScheme(score);
    backgroundSpikes.setColor(scheme.spikes);
    backgroundColor = scheme.background;
    scoreText.setFillColor(scheme.background);

    for (auto& spike: leftSpikes)
        spike.setSpikeColor(scheme.spikes);

    for (auto& spike: rightSpikes)
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

void World::showSpikes(SpikeSide side)
{
    auto& spikes = side == SpikeSide::Left
        ? leftSpikes
        : rightSpikes;

    const int count = getSpikeCount();
    std::vector<int> indices(spikes.size());

    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), rng);

    for (int i = 0; i < count; i++)
        spikes[indices[i]].show();
}

void World::hideSpikes()
{
    for (auto& spike : leftSpikes)
        spike.hide();

    for (auto& spike : rightSpikes)
        spike.hide();
}

int World::getSpikeCount()
{
    if (score <= 1)
        return 2;

    if (score < 5)
    {
        std::uniform_int_distribution<int> dist(2,4);
        return dist(rng);
    }

    const int level = score / 5;

    const int minSpikes = std::min(3 + level, 10);
    const int maxSpikes = std::min(4 + level, 10);

    std::uniform_int_distribution<int> dist(minSpikes, maxSpikes);
    return dist(rng);
}

void World::handleSpikeCollision()
{
    for (auto& spike: leftSpikes)
        handleCollisionWithSpike(spike);

    for (auto& spike: rightSpikes)
        handleCollisionWithSpike(spike);
}

void World::handleCollisionWithSpike(const Spike &spike)
{
    auto spikeBounds = spike.getBounds();
    auto playerBounds = player.getBounds();

    if (spikeBounds.findIntersection(playerBounds) && spike.isVisible())
    {
        player.die();
        std::uniform_real_distribution<float> dist(-6.0f, 6.0f);
        player.bounceHorizontal(dist(rng));
        hideSpikes();
    }
}

sf::Color World::getBackgroundColor() const
{
    return backgroundColor;
}
