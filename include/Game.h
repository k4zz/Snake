#pragma once

#include "SFML/Graphics.hpp"

#include "Snake.h"

class Game
{
public:
    Game(sf::RenderWindow*);

    void gameLoop();

private:

    void calculate();
    void draw();

    sf::RenderWindow* window;
    Snake snake = Snake(nullptr);

    sf::Vector2i snakeNextDirection;
};
