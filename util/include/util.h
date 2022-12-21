#ifndef _UTIL_H
#define _UTIL_H

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <math.h>
#include <set>

namespace utl{
    constexpr double deg2rad = M_PI / 180;

    sf::Vector2f get_topleft_corner(sf::Vector2f middle, const float width, const float height);
    
    void build_rectangle(sf::ConvexShape& target, const sf::Vector2<float>& middle, const float width, const float height);

    void clamp_vector(const float x_minimum, const float x_maximum, const float y_minimum, const float y_maximum, sf::Vector2f& target);

    sf::Vector2f get_random_launch_vector();

    bool intersect(float a1, float a2, float b1, float b2);

    sf::Vector2f get_new_vector(const float player_y, const float player_height, const float ball_y, const sf::Vector2f old_dir);

    sf::Vector2f normalize(sf::Vector2f vector);

    bool key_down(const sf::Keyboard::Key& key, std::set<sf::Keyboard::Key>& pressed_last_frame);

    struct CollisionData{
        sf::Vector2f closest_point;
        bool collided;
    };

    CollisionData get_collision_data(const sf::Vector2f player_pos, const sf::Vector2f player_dimension, const sf::Vector2f ball_pos, const float ball_radius);
}

#endif