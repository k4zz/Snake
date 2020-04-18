#include "Game.h"

#include <iostream>

Game::Game(sf::RenderWindow *_window)
        : window(_window)
        , snake(_window)
        , snakeNextDirection(sf::Vector2i(1,0))
        , device(std::random_device())
        , randomGenerator(std::mt19937(std::time(0)))
        , randomFoodPosition(std::uniform_int_distribution<int>(0,7))
        , food(Food(_window, sf::Vector2i(randomFoodPosition(randomGenerator), randomFoodPosition(randomGenerator))))
{

}

void Game::gameLoop()
{

    while (window->isOpen())
    {
        sf::Event event;

        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

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
                        window->close();
                }
            }

        }

        // calculation phase
        snake.moveBody(snakeNextDirection);

        if(isOnFood())
        {
            snake.ateFood();
        }

        // draw phase
        draw();

    }
}

void Game::draw()
{

    window->clear();
    food.draw();
    snake.draw();
    window->display();
}

bool Game::isOnFood()
{
    return food.getPosition() == snake.getHeadPosition();
}
