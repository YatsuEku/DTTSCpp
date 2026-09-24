#pragma once

#include <SFML/Graphics.hpp>

#include "BackgroundColors.h"
#include "Player.h"
#include "ContentLoader.h"
#include "core/GameState.h"
#include <random>

#include "Spike.h"

constexpr int WORLD_WIDTH = 540;
constexpr int WORLD_HEIGHT = 960;
constexpr float TOP_SPIKES_HEIGHT = 45.0f;
constexpr float BOTTOM_SPIKES_HEIGHT = 70.0f;

class World
{
public:
    explicit World(const ContentLoader& content);

    void draw(sf::RenderTarget& target) const;
    void update(float deltaTime);
    void onGameStateChanged(GameState newState);
    [[nodiscard]] sf::Color getBackgroundColor() const;

private:
    ContentLoader content;
    Player player;
    sf::Sprite backgroundSpikes;
    sf::Sprite backgroundScore;
    sf::Color backgroundColor;
    sf::Text scoreText;
    sf::Sound pointSound;
    std::mt19937 rng{std::random_device{}()};
    std::vector<Spike> leftSpikes;
    std::vector<Spike> rightSpikes;
    SpikeSide currentSide = SpikeSide::Right;
    int score = 0;

    void initializeSpikes();
    void setScoreColors();
    std::string getScoreText() const;
    void showSpikes(SpikeSide side);
    void hideSpikes();
    int getSpikeCount();
    void handleSpikeCollision();
    void handleCollisionWithSpike(const Spike& spike);

    static inline const BackgroundColorScheme& getBackgroundColorScheme(int score)
    {
        for (const auto& scheme : BACKGROUND_COLOR_SCHEMES)
        {
            if (score >= scheme.minScore && score <= scheme.maxScore)
                return scheme;
        }

        return BACKGROUND_COLOR_SCHEMES.back();
    }
};
