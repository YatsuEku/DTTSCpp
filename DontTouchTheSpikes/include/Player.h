#pragma once

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable
{
public:

    void update(float deltaTime);
private:
    sf::Sprite sprite;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};