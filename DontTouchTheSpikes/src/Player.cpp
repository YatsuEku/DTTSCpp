#include "Player.h"
#include <math.h>
#include "world/World.h"

Player::Player(const sf::Texture& upTexture, const sf::Texture& downTexture,  sf::Vector2f position)
    : upTexture(upTexture), downTexture(downTexture), sprite(downTexture), animationMode(std::nullopt)
{
    sprite.setPosition(position);
    sprite.setOrigin(sprite.getLocalBounds().getCenter());
    sprite.setScale({0.65f, 0.65f});
}

void Player::update(float deltaTime)
{
    if (!isPlaying)
    {
        if (animationMode.has_value())
        {
            switch (animationMode.value())
            {
                case PlayerAnimationMode::MenuAnimation:
                    updateMenuAnimation(deltaTime);
                    break;

                default:
                    break;
            }
        }
    }
    else
    {
        sf::Vector2f newPos = sprite.getPosition();
        newPos.x += direction * HORIZONTAL_VELOCITY * deltaTime;
        sprite.setPosition(newPos);
    }
}

void Player::bounceHorizontal()
{
    direction *= -1;
    sf::Vector2f scale = sprite.getScale();
    sprite.setScale({-scale.x, scale.y});
}

sf::FloatRect Player::getBounds() const
{
    return sprite.getGlobalBounds();
}

void Player::updateMenuAnimation(float deltaTime)
{
    float oldY = sprite.getPosition().y;
    float newY = menuAnimationStartPosY + std::sin(menuAnimationTime * MENU_ANIMATION_SPEED) * MENU_ANIMATION_AMPLITUDE;
    sprite.setPosition({sprite.getPosition().x, newY});

    if (oldY > newY)
        sprite.setTexture(downTexture);
    else
        sprite.setTexture(upTexture);

    menuAnimationTime += deltaTime;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

void Player::playMenuAnimation()
{
    animationMode = PlayerAnimationMode::MenuAnimation;
    menuAnimationStartPosY = sprite.getPosition().y;
}

void Player::startPlaying()
{
    isPlaying = true;
    animationMode = std::nullopt;
}
