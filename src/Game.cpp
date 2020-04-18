#include "Game.h"

#include <iostream>
#include <memory>

Game::Game(sf::RenderWindow& _window, sf::Font& _font)
        : window(_window)
          , font(_font)
          , snake(new Snake(_window))
          , gameState(GameState::RunGame)
          , snakeNextDirection(sf::Vector2i(1, 0))
          , randomGenerator(randomDevice())
          , randomFoodPosition(std::uniform_int_distribution<int>(0, 7))
          , food(new Food(_window, sf::Vector2i(randomFoodPosition(randomGenerator), randomFoodPosition(randomGenerator))))
{}

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
                        snakeNextDirection.x = 1;
                        snakeNextDirection.y = 0;
                        break;
                    case sf::Keyboard::Up:
                        snakeNextDirection.x = 0;
                        snakeNextDirection.y = -1;
                        break;
                    case sf::Keyboard::Left:
                        snakeNextDirection.x = -1;
                        snakeNextDirection.y = 0;
                        break;
                    case sf::Keyboard::Down:
                        snakeNextDirection.x = 0;
                        snakeNextDirection.y = 1;
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
            break;
        }

        if (isSnakeOnFood())
        {
            snake->ateFood();
            createNewFood();
        }

        // draw phase
        draw();
    }
}


void Game::gameOverLoop()
{
    sf::Text text;
    text.setFont(font);
    text.setString("Game Over");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(window.getSize().x / 2.0f,
                                  window.getSize().y / 2.0f));
    window.draw(text);

    while (gameState == GameState::GameOver)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                setDefaultState();
                gameState = GameState::RunGame;
            }
        }
    }
}


void Game::draw()
{
    window.clear();
    food->draw();
    snake->draw();
    window.display();
}

bool Game::isSnakeOnFood()
{
    return food->getPosition() == snake->getHeadPosition();
}

bool Game::isSnakeDead()
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
        food->setNewPosition(sf::Vector2i(
                randomFoodPosition(randomGenerator),
                randomFoodPosition(randomGenerator)));
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
    snake = std::make_unique<Snake>(window);
    food = std::make_unique<Food>(window, sf::Vector2i(randomFoodPosition(randomGenerator), randomFoodPosition(randomGenerator)));
    snakeNextDirection = sf::Vector2i(1, 0);
}
