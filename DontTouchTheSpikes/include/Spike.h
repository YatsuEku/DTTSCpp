#pragma once
#include <SFML/Graphics.hpp>

enum class SpikeSide
{
    Left,
    Right
};

class Spike : public sf::Drawable
{
public:
    Spike(const sf::Texture& spikeTexture, sf::Vector2f position, SpikeSide side);
    void setSpikeColor(const sf::Color& color);
    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};