#include "Player.h"

Player::Player(const sf::Texture& texture, sf::Vector2f position)
    : sprite(texture)
{
    sprite.setPosition(position);
}

void Player::update(float deltaTime)
{

}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}