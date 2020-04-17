#include "Snake.h"

class RectangleShape;

class RenderWindow;

Snake::Snake(sf::RenderWindow* _window)
        : window(_window)
{
    for (int initialBodyLenght = 0; initialBodyLenght < 4; initialBodyLenght++)
    {
        auto initSnakePart = sf::RectangleShape(sf::Vector2f(50, 50));
        initSnakePart.setFillColor(sf::Color(sf::Color::White));
        initSnakePart.setPosition(200 - initialBodyLenght * 50, 200);
        snakeParts.emplace_back(initSnakePart);

        auto initialBodyDirection = sf::Vector2i(1,0);
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
    lastDir = snakePartsDirections.back();
    snakePartsDirections.pop_back();
    snakePartsDirections.insert(snakePartsDirections.begin(), _direction);

    //TODO: looks so bad :(
    int i = 0;
    for (auto& snakePart : snakeParts)
    {
        snakePart.move(50 * snakePartsDirections.at(i).x, 50 * snakePartsDirections.at(i).y);
        i++;
    }
}

const sf::Vector2f& Snake::getHeadPosition() const
{
    return snakeParts.at(0).getPosition();
}

void Snake::ateFood()
{
    auto newBody = sf::RectangleShape(sf::Vector2f(50,50));
    auto newBodyDir = sf::Vector2i(0,0);
    newBody.setFillColor(sf::Color::White);
    newBody.setPosition(snakeParts.back().getPosition());
    snakeParts.push_back(newBody);
    snakePartsDirections.insert(snakePartsDirections.begin(),newBodyDir);
}