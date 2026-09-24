#include "Spike.h"

Spike::Spike(const sf::Texture& spikeTexture, sf::Vector2f position, SpikeSide side) : sprite(spikeTexture), side(side)
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

void Spike::update(float deltaTime)
{
    if (animationMode.has_value())
    {
        updateAnimation(deltaTime);
    }
}

void Spike::show()
{
    if (isShown)
        return;

    animationTime = 0;
    animationMode = SpikeAnimationMode::ShowingAnimation;
    animationStartPosX = sprite.getPosition().x;

    if (side == SpikeSide::Left)
        animationTargetPosX = sprite.getPosition().x + getBounds().size.x;
    else
        animationTargetPosX = sprite.getPosition().x - getBounds().size.x;

    isShown = true;
}

void Spike::hide()
{
    if (!isShown)
        return;

    animationTime = 0;
    animationMode = SpikeAnimationMode::HidingAnimation;
    animationStartPosX = sprite.getPosition().x;

    if (side == SpikeSide::Left)
        animationTargetPosX = sprite.getPosition().x - getBounds().size.x;
    else
        animationTargetPosX = sprite.getPosition().x + getBounds().size.x;

    isShown = false;
}

bool Spike::isVisible() const
{
    return isShown;
}

sf::FloatRect Spike::getBounds() const
{
    return sprite.getGlobalBounds();
}

void Spike::updateAnimation(float deltaTime)
{
    animationTime += deltaTime;
    const float progress = std::min(
            animationTime / SPIKE_ANIMATION_DURATION,
            1.0f);

    sf::Vector2f newPos = sprite.getPosition();
    newPos.x = std::lerp(animationStartPosX, animationTargetPosX, progress);
    sprite.setPosition(newPos);
}

void Spike::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite);
}


