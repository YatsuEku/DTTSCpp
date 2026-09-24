#pragma once
#include <SFML/Graphics.hpp>

constexpr float SPIKE_ANIMATION_DURATION = 0.2f;

enum class SpikeSide
{
    Left,
    Right
};

enum class SpikeAnimationMode
{
    ShowingAnimation,
    HidingAnimation
};

class Spike : public sf::Drawable
{
public:
    Spike(const sf::Texture& spikeTexture, sf::Vector2f position, SpikeSide side);
    void setSpikeColor(const sf::Color& color);
    void update(float deltaTime);
    void show();
    void hide();
    bool isVisible() const;
    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
    SpikeSide side;
    float animationStartPosX;
    float animationTargetPosX;
    std::optional<SpikeAnimationMode> animationMode;
    bool isShown = false;
    float animationTime = 0.0f;

    void updateAnimation(float deltaTime);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};