#include "util.h"
#include <iostream>
#include <random>
#include <math.h>
#include <algorithm>


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


sf::Vector2f utl::get_random_launch_vector(){
    std::random_device seed;
    std::default_random_engine engine(seed());
    std::uniform_real_distribution<> prob(0, 1.0);

    double launch_angle {prob(engine) * 12 * 60 * deg2rad};
    // std::cout << launch_angle << std::endl;
    sf::Vector2f launch_vec {(float)cos(launch_angle), (float)sin(launch_angle)};
    return launch_vec;
}


bool utl::intersect(float a1, float a2, float b1, float b2){
    if(a1 > a2) std::swap(a1, a2);
    if(b1 > b2) std::swap(b1, b2);
    return (a1 <= b1 && b1 <= a2) || (a1 <= b2 && b2 <= a2);
}


sf::Vector2f utl::get_new_vector(const float player_y, const float player_height, const float ball_y, const sf::Vector2f old_dir){
    double new_angle {((ball_y - player_y) / (player_height / 2)) * 75 * deg2rad};

    sf::Vector2f new_vec((float)cos(new_angle), (float)-sin(new_angle));
    if(old_dir.x > 0){
        new_vec.x *= -1;
    }

    return new_vec;
}


sf::Vector2f utl::normalize(sf::Vector2f vector){
    float norm = sqrt(vector.x * vector.x + vector.y * vector.y);
    vector /= norm;
    return vector;
}


utl::CollisionData utl::get_collision_data(const sf::Vector2f player_pos, const sf::Vector2f player_dimension, const sf::Vector2f ball_pos, const float ball_radius){
    utl::CollisionData col;

    float closest_x {std::min(std::max(player_pos.x - player_dimension.x / 2, ball_pos.x), player_pos.x + player_dimension.x / 2)};
    float closest_y {std::min(std::max(player_pos.y - player_dimension.y / 2, ball_pos.y), player_pos.y + player_dimension.y / 2)};

    col.closest_point = sf::Vector2f(closest_x, closest_y);
    col.collided = ((closest_x - ball_pos.x) * (closest_x - ball_pos.x) + (closest_y - ball_pos.y) * (closest_y - ball_pos.y) <= ball_radius * ball_radius);
    return col;
}

