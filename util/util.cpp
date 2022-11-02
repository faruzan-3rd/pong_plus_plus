#include "util.h"
#include <iostream>


sf::Vector2<float> utl::get_topleft_corner(sf::Vector2<float> middle, const float width, const float height){
    middle.x -= width / 2;
    middle.y -= height / 2;
    return middle;
}

void utl::build_rectangle(sf::ConvexShape& target, const sf::Vector2<float>& middle, const float width, const float height){
    if(target.getPointCount() != 4){
        // std::cout << "Point count must be 4" << std::endl;
        return;
    }
    sf::Vector2<float> topleft {utl::get_topleft_corner(middle, width, height)};
    target.setPoint(0, topleft);
    target.setPoint(1, topleft + sf::Vector2f(width, 0));
    target.setPoint(2, topleft + sf::Vector2f(width, height));
    target.setPoint(3, topleft + sf::Vector2f(0, height));
}


void utl::clamp_vector(const float x_minimum, const float x_maximum, const float y_minimum, const float y_maximum, sf::Vector2f& target){
    target.x = std::max(x_minimum, std::min(x_maximum, target.x));
    target.y = std::max(y_minimum, std::min(y_maximum, target.y));
}

