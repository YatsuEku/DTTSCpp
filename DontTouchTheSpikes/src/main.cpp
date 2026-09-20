#include <print>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window{
        sf::VideoMode{{540, 960}},
        "Dont Touch The Spikes"
    };

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.display();
    }

	return 0;
}