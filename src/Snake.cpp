#include "Snake.h"

class RectangleShape;
class RenderWindow;

Snake::Snake(sf::RenderWindow* _window)
:window(_window)
{
    auto snakePart = sf::RectangleShape(sf::Vector2f(50,50));
    snakePart.setFillColor(sf::Color(sf::Color::White));
    snakePart.setPosition(200,200);

    snakeBody.push_back(snakePart);
}

void Snake::drawSnakeBody()
{
    for (const auto snakePart : snakeBody)
    {
        window->draw(snakePart);
    }
}

void Snake::moveSnakeBody(const sf::Vector2i& _direction)
{
    for (auto& snakePart : snakeBody)
    {
        snakePart.move(50 * _direction.x, 50 * _direction.y);
    }
}
