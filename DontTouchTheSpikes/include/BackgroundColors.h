#pragma once

#include <SFML/Graphics.hpp>
#include <array>

struct BackgroundColorScheme
{
    int minScore;
    int maxScore;

    sf::Color background;
    sf::Color spikes;
};

inline const std::array<BackgroundColorScheme, 14> BACKGROUND_COLOR_SCHEMES = {
    BackgroundColorScheme{0, 4, sf::Color{235, 235, 235}, sf::Color{128, 128, 128}},
    BackgroundColorScheme{5, 9, sf::Color{222, 234, 240}, sf::Color{99, 117, 128}},
    BackgroundColorScheme{10, 14, sf::Color{244, 232, 225}, sf::Color{128, 106, 99}},
    BackgroundColorScheme{15, 19, sf::Color{232, 241, 222}, sf::Color{116, 128, 99}},
    BackgroundColorScheme{20, 24, sf::Color{230, 225, 244}, sf::Color{107, 99, 128}},
    BackgroundColorScheme{25, 29, sf::Color{114, 114, 114}, sf::Color{255, 255, 255}},
    BackgroundColorScheme{30, 34, sf::Color{0, 106, 132}, sf::Color{0, 190, 236}},
    BackgroundColorScheme{35, 39, sf::Color{40, 132, 1}, sf::Color{128, 237, 0}},
    BackgroundColorScheme{40, 44, sf::Color{0, 37, 132}, sf::Color{0, 106, 236}},
    BackgroundColorScheme{45, 49, sf::Color{132, 0, 62}, sf::Color{236, 0, 100}},
    BackgroundColorScheme{50, 54, sf::Color{248, 170, 59}, sf::Color{255, 255, 255}},
    BackgroundColorScheme{55, 59, sf::Color{13, 173, 249}, sf::Color{255, 255, 255}},
    BackgroundColorScheme{60, 64, sf::Color{157, 25, 247}, sf::Color{255, 255, 255}},
    BackgroundColorScheme{65, 999999, sf::Color{0, 106, 132}, sf::Color{0, 190, 236}},
};
