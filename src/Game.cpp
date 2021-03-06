#include "Game.h"

#include <iostream>
#include <memory>
#include <chrono>

Game::Game(sf::RenderWindow& _window, sf::Font& _font)
        : window(_window)
        , font(_font)
        , snake(new Snake(TILE_SIZE))
        , gameState(GameState::RunGame)
        , score(0)
        , snakeNextDirection(sf::Vector2i(1, 0))
        , randomGenerator(std::chrono::steady_clock::now().time_since_epoch().count())
        , randomFoodPosition(std::uniform_int_distribution<int>(0, (window.getSize().x / TILE_SIZE.x) - 1))
        , food(new Food(sf::Vector2f(0, 0), TILE_SIZE))
{
    createNewFood();
}

void Game::startGame()
{
    while (window.isOpen())
    {
        switch (gameState)
        {
            case GameState::RunGame:
                mainGameLoop();
                break;
            case GameState::GameOver:
                gameOverLoop();
                break;
        }
    }
}

void Game::mainGameLoop()
{
    while (gameState == GameState::RunGame)
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Right:
                        if (snake->getHeadDirection().x != -1)
                        {
                            snakeNextDirection.x = 1;
                            snakeNextDirection.y = 0;
                        }
                        break;
                    case sf::Keyboard::Up:
                        if (snake->getHeadDirection().y != 1)
                        {
                            snakeNextDirection.x = 0;
                            snakeNextDirection.y = -1;
                        }
                        break;
                    case sf::Keyboard::Left:
                        if (snake->getHeadDirection().x != 1)
                        {
                            snakeNextDirection.x = -1;
                            snakeNextDirection.y = 0;
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (snake->getHeadDirection().y != -1)
                        {
                            snakeNextDirection.x = 0;
                            snakeNextDirection.y = 1;
                        }
                        break;
                    case sf::Keyboard::Escape:
                        window.close();
                }
            }
        }

        // calculation phase
        snake->moveBody(snakeNextDirection);

        if (isSnakeDead())
        {
            gameState = GameState::GameOver;
            return;
        }

        if (isSnakeOnFood())
        {
            snake->ateFood();
            score++;
            createNewFood();
        }

        // draw phase
        std::string scoreStr = "Snake | Score: " + std::to_string(score);
        window.setTitle(scoreStr);
        drawScene();
    }
}


void Game::gameOverLoop()
{
    drawGameOver();

    sf::Event event;
    while (gameState == GameState::GameOver)
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                setDefaultState();
                gameState = GameState::RunGame;
            }
        }
    }
}

void Game::drawGameOver() const
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(50);
    text.setString("Game Over");
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(window.getSize().x / 2.0f,
                                  window.getSize().y / 2.0f));
    text.setFillColor(sf::Color::White);
    window.clear();
    window.draw(*snake);
    window.draw(*food);
    window.draw(text);
    window.display();
}


void Game::drawScene() const
{
    window.clear();
    window.draw(*food);
    window.draw(*snake);
    window.display();
}

bool Game::isSnakeOnFood() const
{
    return food->getPosition() == snake->getHeadPosition();
}

bool Game::isSnakeDead() const
{
    auto const& snakePosition = snake->getHeadPosition();
    auto const& windowSize = window.getSize();

    return snakePosition.x < 0 ||
           snakePosition.x >= windowSize.x ||
           snakePosition.y < 0 ||
           snakePosition.y >= windowSize.y ||
           snake->isSnakeDead();
}

void Game::createNewFood()
{
    bool invalidPosition = true;
    while (invalidPosition)
    {
        food->setPosition(sf::Vector2f(
                randomFoodPosition(randomGenerator) * TILE_SIZE.x,
                randomFoodPosition(randomGenerator) * TILE_SIZE.y));
        invalidPosition = false;
        for (const auto& bodyPart : snake->getBodyParts())
        {
            if (food->getPosition() == bodyPart.getPosition())
            {
                invalidPosition = true;
            }
        }
    }
}

void Game::setDefaultState()
{
    snake = std::make_unique<Snake>(TILE_SIZE);
    food->setPosition(sf::Vector2f(randomFoodPosition(randomGenerator) * TILE_SIZE.x,
                                   randomFoodPosition(randomGenerator) * TILE_SIZE.y));
    snakeNextDirection = sf::Vector2i(1, 0);
    score = 0;
}