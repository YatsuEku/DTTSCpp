#include "Spike.h"

Spike::Spike(const sf::Texture& spikeTexture, sf::Vector2f position, SpikeSide side) : sprite(spikeTexture)
{
    sprite.setPosition(position);
    sprite.setScale({0.8f, 0.8f});
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.getCenter());
    sprite.setRotation(sf::degrees(side == SpikeSide::Left ? 90.0f : -90.0f));
}

void Spike::setSpikeColor(const sf::Color &color)
{
    sprite.setColor(color);
}

sf::FloatRect Spike::getBounds() const
{
    return sprite.getGlobalBounds();
}

void Spike::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite);
}


