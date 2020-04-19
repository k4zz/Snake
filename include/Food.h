#pragma once

#include "SFML/Graphics.hpp"

class Food : public sf::Drawable
{
public:
    explicit Food(const sf::Vector2f&, const sf::Vector2f&);

    const sf::Vector2f& getPosition() const;
    void setPosition(const sf::Vector2f&);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::RectangleShape food;
};