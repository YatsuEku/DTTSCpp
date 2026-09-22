#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

const float MENU_ANIMATION_AMPLITUDE = 30.0f;
const float MENU_ANIMATION_SPEED = 4.5f;

const float HORIZONTAL_VELOCITY = 300.0f;

enum class PlayerAnimationMode
{
    MenuAnimation
};

class Player : public sf::Drawable
{
public:
    Player(const sf::Texture& upTexture, const sf::Texture& downTexture, sf::Vector2f position);

    void playMenuAnimation();
    void startPlaying();
    void update(float deltaTime);
    void bounceHorizontal();
    sf::FloatRect getBounds() const;
private:
    sf::Sprite sprite;
    sf::Texture upTexture;
    sf::Texture downTexture;
    std::optional<PlayerAnimationMode> animationMode;
    float menuAnimationStartPosY;
    float menuAnimationTime;
    float direction = 1; // 1 right -1 left
    bool isPlaying = false;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void updateMenuAnimation(float deltaTime);
};