#pragma once

#include <SFML/Graphics.hpp>
#include <optional>
#include <SFML/Audio.hpp>

constexpr float MENU_ANIMATION_AMPLITUDE = 30.0f;
constexpr float MENU_ANIMATION_SPEED = 4.5f;

constexpr float HORIZONTAL_VELOCITY = 300.0f;
constexpr float MAX_FALL_SPEED = 900.0f;
constexpr float GRAVITY = 1400.0f;
constexpr float JUMP_VELOCITY = -450.0f;
constexpr float DEATH_Y_BOUNCE_VELOCITY = -900.0f;

constexpr float DEATH_ANIMATION_DURATION = 4.0f;
constexpr float DEATH_ROTATION_SPEED = 1000.0f;
constexpr float BOUNCE_COOLDOWN_DURATION = 0.8f;

enum class PlayerAnimationMode
{
    MenuAnimation,
    DeathAnimation
};

class Player : public sf::Drawable
{
public:
    Player(const sf::Texture& upTexture, const sf::Texture& downTexture, const sf::Texture& deathTexture, const sf::SoundBuffer& jumpSfx, const sf::SoundBuffer& deathSfx, sf::Vector2f position);

    void playMenuAnimation();
    void startPlaying();
    void update(float deltaTime);

    void bounceHorizontal();
    void bounceHorizontal(float direction);
    void bounceVertical(float xDirection, float yDirection);
    void die();
    bool isPlayerDead() const;
    float getVelocityY() const;
    sf::FloatRect getBounds() const;
    bool isHorizontalBounceOnCooldown() const;
private:
    sf::Sprite sprite;
    sf::Texture upTexture;
    sf::Texture downTexture;
    sf::Texture deathTexture;
    sf::Sound jumpSfx;
    sf::Sound deathSfx;
    std::optional<PlayerAnimationMode> animationMode;
    float menuAnimationStartPosY = 0;
    float animationTime = 0;
    float direction = 1; // 1 right -1 left
    float velocityY = 0;
    float hBounceCooldownTime = 0.0f;
    bool isPlaying = false;
    bool isDead = false;
    bool wasJumpPressed = false;
    bool isBounceOnCooldown = false;

    void updateMenuAnimation(float deltaTime);
    void updateJumpAnimation(float deltaTime);
    void updateDeathAnimation(float deltaTime);
    void updateBounceCooldown(float deltaTime);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};