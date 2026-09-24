#include "core/Game.h"
#include <print>
#include <fstream>

Game::Game()
    : content("assets"), world(content), window(sf::VideoMode{{540, 960}}, "Dont Touch The Spikes"),
      state(GameState::Launching), scoreText(content.getFont(FontId::Menu)), highScoreText(content.getFont(FontId::Menu)), newHighScoreText(content.getFont(FontId::Menu), "New high score!"), tapToPlayText(content.getFont(FontId::Menu), "Tap to play")
{
    highScoreText.setString(getHighScoreString());
    scoreText.setString(getScoreString());
    tapToPlayText.setFillColor(sf::Color::Black);

    auto tapToPlayBounds = tapToPlayText.getGlobalBounds();
    tapToPlayText.setPosition({window.getSize().x / 2.0f - tapToPlayBounds.size.x / 2.0f, window.getSize().y / 2.0f - 100.0f});

    auto scoreBounds = scoreText.getGlobalBounds();
    scoreText.setPosition({window.getSize().x / 2.0f - scoreBounds.size.x / 2.0f, 200.0f});

    auto highScoreBounds = highScoreText.getGlobalBounds();
    highScoreText.setPosition({window.getSize().x / 2.0f - highScoreBounds.size.x / 2.0f, 200.0f + scoreBounds.size.y + 6.0f});

    auto newHighScoreBounds = newHighScoreText.getGlobalBounds();
    newHighScoreText.setPosition({window.getSize().x / 2.0f - newHighScoreBounds.size.x / 2.0f, 200.0f + highScoreBounds.size.y + scoreBounds.size.y + 12.0f});
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
    load();
}

void Game::load()
{
    loadGame();
    world.setHighestScore(loadedHighScore);
}

void Game::update(float deltaTime)
{
    while (const auto& event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
    }

    const bool mousePressed =
        sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    const bool pressedOnce =
        mousePressed && !mousePressedLastFrame;

    if (pressedOnce)
    {
        if (state == GameState::Menu)
            setState(GameState::Playing);
        else if (state == GameState::GameOver)
            setState(GameState::Menu);
    }

    mousePressedLastFrame = mousePressed;

    world.update(deltaTime);

    if (world.isGameOver() && state == GameState::Playing)
    {
        setState(GameState::GameOver);
        onGameOver();
    }

    if (state == GameState::GameOver)
    {
        updateTextAnimation(deltaTime);
    }
}

void Game::draw()
{
    window.clear(world.getBackgroundColor());

    world.draw(window);
    if (state == GameState::Menu)
        window.draw(tapToPlayText);

    if (state == GameState::GameOver)
    {
        window.draw(scoreText);
        window.draw(highScoreText);
        if (world.isNewHighScore())
            window.draw(newHighScoreText);
    }

    window.display();
}

void Game::setState(GameState newState)
{
    if (state == newState)
        return;

    state = newState;
    world.onGameStateChanged(newState);
}

void Game::onGameOver()
{
    gameOverTextAnimationTime = 0.0f;
    alphaColor = 0;
    scoreText.setString(getScoreString());
    highScoreText.setString(getHighScoreString());
    saveGame();
}

void Game::updateTextAnimation(float deltaTime)
{
    gameOverTextAnimationTime += deltaTime;
    const float progress = std::min(
        gameOverTextAnimationTime / FADE_IN_TEXT_DURATION,
        1.0f);

    alphaColor = static_cast<std::uint8_t>(std::lerp(0, 255, progress));

    sf::Color newColor(0, 0, 0, alphaColor);
    highScoreText.setFillColor(newColor);
    scoreText.setFillColor(newColor);
    if (world.isNewHighScore())
        newHighScoreText.setFillColor(newColor);
}

void Game::saveGame()
{
    std::ofstream(SAVE_FILE_NAME) << world.getHighestScore();
}

void Game::loadGame()
{
    std::ifstream file(SAVE_FILE_NAME);

    if (!(file >> loadedHighScore))
        loadedHighScore = 0;
}

std::string Game::getHighScoreString() const
{
    return "High score: " + std::to_string(world.getHighestScore());
}

std::string Game::getScoreString() const
{
    return "Score: " + std::to_string(world.getScore());
}
