#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

using SnakeParts = std::vector<sf::RectangleShape>;
using SnakePartsDirections = std::vector<sf::Vector2i>;


class Snake
{
public:
    Snake(sf::RenderWindow* window);

    void moveBody(sf::Vector2i& _direction);

    void draw() const;

    void ateFood();

    const sf::Vector2f& getHeadPosition() const;

    const SnakeParts& getBodyParts() const;

private:
    SnakeParts snakeParts;
    SnakePartsDirections snakePartsDirections;
    sf::Vector2i lastDir;

    sf::RenderWindow* window;
    bool snakeEats;
};