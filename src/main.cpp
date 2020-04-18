#include <SFML/Graphics.hpp>
#include "../include/Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "Snake", sf::Style::Close);
    window.setFramerateLimit(2);
    Game game(window);
    game.startGame();

    return 0;
}