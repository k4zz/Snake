#include "Food.h"

Food::Food(sf::RenderWindow* _window, sf::Vector2i _position)
        : window(_window)
          , food(sf::RectangleShape(sf::Vector2f(50, 50)))
{
    auto foodPosition = sf::Vector2f(_position.x * 50, _position.y * 50);
    food.setPosition(foodPosition);
    food.setFillColor(sf::Color::Red);
}

void Food::draw() const
{
    window->draw(food);
}

const sf::Vector2f& Food::getPosition() const
{
    return food.getPosition();
}

