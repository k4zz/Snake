#include "Snake.h"

Snake::Snake(sf::RenderWindow& _window, const sf::Vector2f& _tileSize)
        : window(_window)
        , snakeEats(false)
{
    for (int initialBodyLenght = 0; initialBodyLenght < 3; initialBodyLenght++)
    {
        auto initSnakePart = sf::RectangleShape(_tileSize);
        initSnakePart.setFillColor(sf::Color(sf::Color::Green));
        initSnakePart.setPosition(sf::Vector2f(3 * _tileSize.x - initialBodyLenght * _tileSize.x, 4 * _tileSize.y));
        snakeParts.emplace_back(initSnakePart);

        auto initialBodyDirection = sf::Vector2i(1, 0);
        snakePartsDirections.emplace_back(initialBodyDirection);
    }
}

void Snake::draw() const
{
    for (const auto& snakePart : snakeParts)
    {
        window.draw(snakePart);
    }
}

void Snake::moveBody(const sf::Vector2i& _direction)
{
    // push new position into vector of directions
    currentDirection = _direction;
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
            it->move(sf::Vector2f(it->getSize().x * snakePartsDirections.at(i).x,
                                  it->getSize().y * snakePartsDirections.at(i).y));
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
    auto newBody = sf::RectangleShape(sf::Vector2f(snakeParts.at(0).getSize().x, snakeParts.at(0).getSize().y));
    newBody.setFillColor(sf::Color::Green);
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

bool Snake::isSnakeDead()
{
    bool isSnakeDead = false;
    for (auto i = 1; i < snakeParts.size(); i++)
    {
        isSnakeDead = snakeParts.at(0).getGlobalBounds().intersects(snakeParts.at(i).getGlobalBounds());
        if (isSnakeDead)
            return true;
    }

    return false;
}

const sf::Vector2i& Snake::getHeadDirection() const
{
    return currentDirection;
}
