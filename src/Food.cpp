#include "Food.h"

Food::Food(const sf::Vector2f& _position, const sf::Vector2f& _size)
        : food(sf::RectangleShape(_size))
{
    food.setPosition(sf::Vector2f(_position.x, _position.y));
    food.setFillColor(sf::Color::Red);
}

void Food::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(food, states);
}

const sf::Vector2f& Food::getPosition() const
{
    return food.getPosition();
}

void Food::setPosition(const sf::Vector2f& _position)
{
    food.setPosition(_position);
}

