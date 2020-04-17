#include <SFML/Graphics.hpp>
#include "../include/Game.h"

int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(400, 400), "Snake");
    window->setFramerateLimit(5);
    Game game(window);
    game.gameLoop();

    return 0;
}