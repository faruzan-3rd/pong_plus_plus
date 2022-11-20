#include "gameManager.h"
#include "util.h"
#include <iostream>


PongManager::PongManager(sf::RenderWindow& window, const int player_offset,
                         const int player_width, const int player_height,
                         const float player_thickness, const float ball_radius,
                         const float ball_thickness, const float default_player_spd,
                         const float default_ball_spd)
                : screen(window), window_width(window.getSize().x),
                 window_height(window.getSize().y), player_xoffset(player_offset),
                 player_height(player_height), player_width(player_width),
                 player_thickness(player_thickness), ball_radius(ball_radius),
                 ball_thickness(ball_thickness), default_player_spd(default_player_spd),
                 default_ball_spd(default_ball_spd)
{
    setup();
}


void PongManager::setup(){
    leftpl = Player(sf::Vector2f(player_xoffset, window_height / 2), player_width, player_height, player_thickness);
    rightpl = Player(sf::Vector2f(window_width - player_xoffset, window_height / 2), player_width, player_height, player_thickness);

    ball = Ball(sf::Vector2f(window_width / 2, window_height / 2), ball_radius, ball_thickness, utl::get_random_launch_vector(), default_ball_spd);
    clock = sf::Clock();
    last_update = clock.getElapsedTime().asSeconds();
}


void PongManager::render(){
    leftpl.draw(screen);
    rightpl.draw(screen);
    ball.draw(screen);
}


void PongManager::tick(){
    // Move players
    // Player left
    float delta = (clock.getElapsedTime().asMilliseconds() - last_update) / 1000.0f;
    last_update = clock.getElapsedTime().asMilliseconds();

    sf::Vector2f left_new_vec {leftpl.get_position()};
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        left_new_vec += sf::Vector2f(0, -default_player_spd * delta);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        left_new_vec += sf::Vector2f(0, default_player_spd * delta);
    }
    utl::clamp_vector(0, window_width, player_height / 2, window_height - player_height / 2, left_new_vec);
    leftpl.set_position(left_new_vec);

    // Player right
    sf::Vector2f right_new_vec {rightpl.get_position()};
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        right_new_vec += sf::Vector2f(0, -default_player_spd * delta);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        right_new_vec += sf::Vector2f(0, default_player_spd * delta);
    }
    utl::clamp_vector(0, window_width, player_height / 2, window_height - player_height / 2, right_new_vec);
    rightpl.set_position(right_new_vec);


    if(ball.get_position().y <= ball_radius / 2 || ball.get_position().y >= window_height - ball_radius / 2){
        ball.reverse_y_velocity(2 + ball_radius, window_height - 2 - ball_radius);
    }

    const sf::Vector2f player_dim(player_width, player_height);
    const float ball_x {ball.get_position().x};

    // Collision detection with left paddle
    utl::CollisionData left_paddle_col{utl::get_collision_data(leftpl.get_position(), player_dim, ball.get_position(), ball_radius)};
    if(left_paddle_col.collided){
        if((abs(left_paddle_col.closest_point.y) - leftpl.get_position().y) >= player_height / 2){
            ball.reverse_y_velocity(leftpl.get_position().y + player_height / 2 + ball_radius + 1, leftpl.get_position().y - player_height / 2 - ball_radius - 1);
        }
        else{
            ball.collide_with_player(leftpl.get_position().y, player_height, leftpl.get_position().x + player_width / 2 + ball_radius + 1);
        }
    }

    // Collision detection with right paddle
    utl::CollisionData right_paddle_col{utl::get_collision_data(rightpl.get_position(), player_dim, ball.get_position(), ball_radius)};
    if(right_paddle_col.collided){
        if((abs(right_paddle_col.closest_point.y) - rightpl.get_position().y) >= player_height / 2){
            ball.reverse_y_velocity(rightpl.get_position().y + player_height / 2 + ball_radius + 1, rightpl.get_position().y - player_height / 2 - ball_radius - 1);
        }
        else{
            ball.collide_with_player(rightpl.get_position().y, player_height, rightpl.get_position().x - player_width / 2 - ball_radius - 1);
        }
    }


    // Move ball
    ball.move(delta);
}
