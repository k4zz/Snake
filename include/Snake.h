#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

using SnakeParts = std::vector<sf::RectangleShape>;
using SnakePartsDirections = std::vector<sf::Vector2i>;

class Snake : public sf::Drawable
{
public:
    Snake(const sf::Vector2f&);

    void moveBody(const sf::Vector2i& _direction);

    void ateFood();

    const sf::Vector2f& getHeadPosition() const;
    const sf::Vector2i& getHeadDirection() const;
    const SnakeParts& getBodyParts() const;
    bool isSnakeDead();

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    SnakeParts snakeParts;
    SnakePartsDirections snakePartsDirections;

    sf::Vector2i currentDirection;

    bool snakeEats;
};