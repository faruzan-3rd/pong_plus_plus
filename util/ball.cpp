#include "ball.h"


Ball::Ball(const sf::Vector2f pos, const float radius, const float thickness):
        image(sf::CircleShape(radius)), position(pos)
{

    image.setFillColor(sf::Color::Transparent);
    image.setOutlineThickness(thickness);
    image.setOutlineColor(sf::Color::White);
}


void Ball::draw(sf::RenderWindow& window){
    image.setPosition(sf::Vector2f(position.x - image.getRadius() / 2, position.y - image.getRadius() / 2));
    window.draw(image);
}