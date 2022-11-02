#include "playerbar.h"
#include "util.h"
#include <iostream>


Player::Player(const sf::Vector2f& pos, const int width, const int height, const float thickness):
    image(sf::ConvexShape(4)), position(pos), bar_width(width), bar_height(height)
{
    image.setFillColor(sf::Color::Transparent);
    image.setOutlineColor(sf::Color::White);
    image.setOutlineThickness(thickness);
    utl::build_rectangle(image, position, width, height);
}



void Player::draw(sf::RenderWindow& window){
    
    utl::build_rectangle(image, position, bar_width, bar_height);
    window.draw(image);
}


sf::Vector2f Player::get_position() const{
    return position;
}


void Player::set_position(const sf::Vector2f& new_pos){
    position = new_pos;
}