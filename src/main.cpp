#include <iostream>

#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
    sf::Font font;
    if(!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Couldn't load font" << std::endl;
    }

    sf::RenderWindow window(sf::VideoMode(400, 400), "Snake", sf::Style::Close);
    window.setFramerateLimit(2);
    Game game(window, font);
    game.startGame();

    return 0;
}