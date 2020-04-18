#pragma once

#include <random>

#include "SFML/Graphics.hpp"

#include "Snake.h"
#include "Food.h"

class Game
{
public:
    explicit Game(sf::RenderWindow*);

    void gameLoop();

private:

    bool isOnFood();
    void draw();

    std::random_device randomDevice;
    std::mt19937 randomGenerator;
    std::uniform_int_distribution<int> randomFoodPosition;

    sf::RenderWindow* window;

    Snake snake;
    sf::Vector2i snakeNextDirection;

    Food food;
};
