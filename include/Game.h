#pragma once

#include <random>

#include "SFML/Graphics.hpp"

#include "Snake.h"
#include "Food.h"


enum class GameState
{
    RunGame,
    GameOver
};


class Game
{
public:
    Game(sf::RenderWindow& _window);

    void startGame();

private:

    void mainGameLoop();

    void gameOverLoop();

    bool isSnakeOnFood();

    void draw();

    std::random_device randomDevice;
    std::mt19937 randomGenerator;
    std::uniform_int_distribution<int> randomFoodPosition;

    sf::RenderWindow& window;

    Snake snake;
    sf::Vector2i snakeNextDirection;

    Food food;

    GameState gameState;

    bool isSnakeDead();

    void createNewFood();
};
