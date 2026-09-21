#include <SFML/Graphics.hpp>

#include "world/World.h"

int main()
{
    sf::RenderWindow window{
        sf::VideoMode{{540, 960}},
        "Dont Touch The Spikes"
    };

    World world;

    window.setFramerateLimit(60);

    sf::Clock deltaClock;

    while (window.isOpen())
    {
        sf::Time deltaTime = deltaClock.restart();

        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        world.update(deltaTime.asSeconds());

        window.clear();
        world.draw(window);
        window.display();
    }

	return 0;
}