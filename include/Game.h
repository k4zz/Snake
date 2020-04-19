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

namespace
{
    const sf::Vector2f TILE_SIZE(50, 50);
}

class Game
{
public:
    Game(sf::RenderWindow&, sf::Font&);

    void startGame();

private:
    void mainGameLoop();

    void gameOverLoop();

    void draw();

    bool isSnakeDead();

    bool isSnakeOnFood();

    void createNewFood();

    void setDefaultState();

    sf::RenderWindow& window;
    sf::Font& font;

    std::mt19937 randomGenerator;
    std::uniform_int_distribution<int> randomFoodPosition;

    GameState gameState;

    std::unique_ptr<Snake> snake;
    sf::Vector2i snakeNextDirection;

    std::unique_ptr<Food> food;

    int score;
};
