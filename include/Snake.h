#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

using SnakeParts = std::vector<sf::RectangleShape>;
using SnakePartsDirections = std::vector<sf::Vector2i>;

class Snake
{
public:
    Snake(sf::RenderWindow& window, const sf::Vector2f&);

    void moveBody(const sf::Vector2i& _direction);
    void draw() const;

    void ateFood();

    const sf::Vector2f& getHeadPosition() const;
    const sf::Vector2i& getHeadDirection() const;
    const SnakeParts& getBodyParts() const;
    bool isSnakeDead();

private:
    SnakeParts snakeParts;
    SnakePartsDirections snakePartsDirections;

    sf::Vector2i currentDirection;

    sf::RenderWindow& window;
    bool snakeEats;
};