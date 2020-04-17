#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

class Snake
{
public:
    Snake(sf::RenderWindow* window);
    void moveSnakeBody(const sf::Vector2i& _direction);
    void drawSnakeBody();

private:
    std::vector<sf::RectangleShape> snakeBody;
    std::vector<sf::Vector2i> snakeDirections;

    sf::RenderWindow* window;
};