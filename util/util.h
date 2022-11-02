#ifndef _UTIL_H
#define _UTIL_H

#include <SFML/Graphics.hpp>

namespace utl{
    sf::Vector2f get_topleft_corner(sf::Vector2f middle, const float width, const float height);
    
    void build_rectangle(sf::ConvexShape& target, const sf::Vector2<float>& middle, const float width, const float height);

    void clamp_vector(const float x_minimum, const float x_maximum, const float y_minimum, const float y_maximum, sf::Vector2f& target);
}

#endif