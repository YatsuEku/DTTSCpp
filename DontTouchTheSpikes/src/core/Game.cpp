#include "core/Game.h"

Game::Game()
    : content("assets"), world(content), window(sf::VideoMode{{540, 960}}, "Dont Touch The Spikes"), state(GameState::Launching)
{
}

void Game::run()
{
    init();
    sf::Clock clock;

    setState(GameState::Menu);

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        update(deltaTime.asSeconds());
        draw();
    }
}

void Game::init()
{
    window.setFramerateLimit(60);
}

void Game::update(float deltaTime)
{
    while (const auto& event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
    }

    world.update(deltaTime);
}

void Game::draw()
{
    window.clear(world.getBackgroundColor());
    world.draw(window);
    window.display();
}

void Game::setState(GameState newState)
{
    if (state == newState)
        return;

    state = newState;
    world.onGameStateChanged(newState);
}