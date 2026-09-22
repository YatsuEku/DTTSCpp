#pragma once

#include <SFML/Graphics.hpp>

#include "BackgroundColors.h"
#include "Player.h"
#include "ContentLoader.h"
#include "core/GameState.h"

const int WORLD_WIDTH = 540;
const int WORLD_HEIGHT = 960;

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
    int score = 0;

    void setScoreColors();

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
