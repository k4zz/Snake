#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

namespace
{
    using SnakeParts = std::vector<sf::RectangleShape>;
    using SnakePartsDirections = std::vector<sf::Vector2i>;
}

class Snake
{
public:
    Snake(sf::RenderWindow* window);

    void moveSnakeBody(sf::Vector2i& _direction);

    void drawSnakeBody();

private:
    SnakeParts snakeParts;
    SnakePartsDirections snakePartsDirections;

    sf::RenderWindow* window;
};