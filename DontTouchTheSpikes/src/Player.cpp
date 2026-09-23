#include "Player.h"
#include <cmath>
#include <print>
#include "world/World.h"

Player::Player(const sf::Texture& upTexture, const sf::Texture& downTexture, const sf::Texture& deathTexture, const sf::SoundBuffer& jumpSfx, const sf::SoundBuffer& deathSfx, sf::Vector2f position)
    : sprite(downTexture), upTexture(upTexture), downTexture(downTexture), deathTexture(deathTexture), jumpSfx(jumpSfx), deathSfx(deathSfx), animationMode(std::nullopt)
{
    sprite.setPosition(position);
    sprite.setOrigin(sprite.getLocalBounds().getCenter());
    sprite.setScale({0.65f, 0.65f});

    this->jumpSfx.setVolume(40);
}

void Player::update(float deltaTime)
{
    if (animationMode.has_value())
    {
        switch (animationMode.value())
        {
            case PlayerAnimationMode::MenuAnimation:
                updateMenuAnimation(deltaTime);
                break;

            case PlayerAnimationMode::DeathAnimation:
                updateDeathAnimation(deltaTime);
                break;

            default:
                break;
        }
    }

    if (isPlaying && !isDead)
    {
        sf::Vector2f newPos = sprite.getPosition();
        newPos.x += direction * HORIZONTAL_VELOCITY * deltaTime;

        const bool jumpPressed =
            sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

        const bool jumpJustPressed =
            jumpPressed && !wasJumpPressed;

        wasJumpPressed = jumpPressed;

        if (jumpJustPressed)
        {
            velocityY = JUMP_VELOCITY;

            jumpSfx.stop();
            jumpSfx.play();
        }
        else
            velocityY += GRAVITY * deltaTime;

        velocityY = std::min(velocityY, MAX_FALL_SPEED);
        newPos.y += velocityY * deltaTime;

        sprite.setPosition(newPos);
        updateJumpAnimation(deltaTime);
    }
    else if (isDead)
    {
        sf::Vector2f newPos = sprite.getPosition();
        newPos.x += direction * HORIZONTAL_VELOCITY * deltaTime;
        velocityY += GRAVITY * deltaTime;
        velocityY = std::min(velocityY, MAX_FALL_SPEED);
        newPos.y += velocityY * deltaTime;
        sprite.setPosition(newPos);
    }
}

void Player::bounceHorizontal()
{
    direction *= -1;
    sf::Vector2f scale = sprite.getScale();
    sprite.setScale({-scale.x, scale.y});
}

void Player::bounceHorizontal(float direction)
{
    this->direction = direction;
}

void Player::bounceVertical(float xDirection, float yDirection)
{
    velocityY = DEATH_Y_BOUNCE_VELOCITY * yDirection;
    direction = xDirection;
}

void Player::die()
{
    if (isDead)
        return;

    isPlaying = false;
    isDead = true;
    animationMode = PlayerAnimationMode::DeathAnimation;
    animationTime = 0;
    sprite.setTexture(deathTexture);
    deathSfx.play();
}

bool Player::isPlayerDead() const
{
    return isDead;
}

float Player::getVelocityY() const
{
    return velocityY;
}

sf::FloatRect Player::getBounds() const
{
    return sprite.getGlobalBounds();
}

void Player::updateMenuAnimation(float deltaTime)
{
    const float oldY = sprite.getPosition().y;
    float newY = menuAnimationStartPosY + std::sin(animationTime * MENU_ANIMATION_SPEED) * MENU_ANIMATION_AMPLITUDE;
    sprite.setPosition({sprite.getPosition().x, newY});

    if (oldY > newY)
        sprite.setTexture(downTexture);
    else
        sprite.setTexture(upTexture);

    animationTime += deltaTime;
}

void Player::updateJumpAnimation(float deltaTime)
{
    if (velocityY > 0)
        sprite.setTexture(downTexture);
    else
        sprite.setTexture(upTexture);
}

void Player::updateDeathAnimation(float deltaTime)
{
    animationTime += deltaTime;
    const float progress = std::min(
        animationTime / DEATH_ANIMATION_DURATION,
        DEATH_ANIMATION_DURATION);

    sf::Color currentColor = sprite.getColor();
    currentColor.a = static_cast<std::uint8_t>(std::lerp(currentColor.a, 0, progress));
    sprite.setColor(currentColor);

    sprite.rotate(sf::degrees(DEATH_ROTATION_SPEED * deltaTime));
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
