#pragma once

#include "SFML/Graphics.hpp"

class Food
{
public:
    Food(sf::RenderWindow* _window, sf::Vector2i _position);

    const sf::Vector2f& getPosition() const;
    void draw() const;

private:
    sf::RectangleShape food;

    sf::RenderWindow* window;
};