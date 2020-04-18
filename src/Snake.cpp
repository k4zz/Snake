#include "Snake.h"

class RectangleShape;

class RenderWindow;

Snake::Snake(sf::RenderWindow* _window)
        : window(_window)
          , snakeEats(false)
{
    for (int initialBodyLenght = 0; initialBodyLenght < 4; initialBodyLenght++)
    {
        auto initSnakePart = sf::RectangleShape(sf::Vector2f(50, 50));
        initSnakePart.setFillColor(sf::Color(sf::Color::White));
        initSnakePart.setPosition(200 - initialBodyLenght * 50, 200);
        snakeParts.emplace_back(initSnakePart);

        auto initialBodyDirection = sf::Vector2i(1, 0);
        snakePartsDirections.emplace_back(initialBodyDirection);
    }
}

void Snake::draw() const
{
    for (const auto& snakePart : snakeParts)
    {
        window->draw(snakePart);
    }
}

void Snake::moveBody(sf::Vector2i& _direction)
{
    // push new position into vector of directions
    lastDir = snakePartsDirections.back();
    snakePartsDirections.pop_back();
    snakePartsDirections.insert(snakePartsDirections.begin(), _direction);

    // shift all parts of snake according to direction vector
    int i = 0;
    for (auto it = snakeParts.begin(); it != snakeParts.end(); ++it)
    {
        // if snake eats do not shift last part of snake
        if ((std::next(it) == snakeParts.end()) && snakeEats)
        {
            snakeEats = false;
        }
        else
        {
            it->move(50 * snakePartsDirections.at(i).x, 50 * snakePartsDirections.at(i).y);
            i++;
        }
    }
}

const sf::Vector2f& Snake::getHeadPosition() const
{
    return snakeParts.at(0).getPosition();
}

void Snake::ateFood()
{
    snakeEats = true;

    // create new body part
    auto newBody = sf::RectangleShape(sf::Vector2f(50, 50));
    newBody.setFillColor(sf::Color::White);
    newBody.setPosition(snakeParts.back().getPosition());
    snakeParts.push_back(newBody);

    // set direction for new body part
    auto newBodyDir = sf::Vector2i(0, 0);
    snakePartsDirections.push_back(newBodyDir);
}

const SnakeParts& Snake::getBodyParts() const
{
    return snakeParts;
}
