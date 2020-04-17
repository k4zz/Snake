#include "Game.h"

Game::Game(sf::RenderWindow *_window)
        : window(_window)
        , snake(_window)
        , snakeNextDirection(sf::Vector2i(1,0))
{}

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
                }
            }

        }

        snake.moveSnakeBody(snakeNextDirection);
        draw();

    }
}

void Game::draw()
{

    window->clear();
    snake.drawSnakeBody();
    window->display();
}
