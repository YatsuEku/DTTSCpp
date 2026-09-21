#pragma once

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable
{
public:
    Player(const sf::Texture& texture, sf::Vector2f position);

    void update(float deltaTime);
private:
    sf::Sprite sprite;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};