#include "Snake.h"

class RectangleShape;
class RenderWindow;

Snake::Snake(sf::RenderWindow* _window)
:window(_window)
{
    snakeHead = sf::RectangleShape(sf::Vector2f(50,50));
    snakeHead.setFillColor(sf::Color(sf::Color::White));
    snakeHead.setPosition(200,200);
}

void Snake::drawSnakeBody()
{
    window->draw(snakeHead);
}

void Snake::moveSnakeBody(const sf::Vector2i& _direction)
{
    snakeHead.move(50 * _direction.x, 50 * _direction.y );
}
