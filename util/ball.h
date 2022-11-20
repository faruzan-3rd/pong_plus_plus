#ifndef _BALL_H
#define _BALL_H


#include <SFML/Graphics.hpp>


class Ball{
    public:
        Ball() = default;
        Ball(const sf::Vector2f pos, const float radius, const float thickness, const sf::Vector2f default_dir, const float default_speed);

        void draw(sf::RenderWindow& window);

        void move(const float delta);

        const sf::Vector2f& get_position() const;

        void reverse_y_velocity(const float reset_y1, const float reset_y2);

        void collide_with_player(const float player_y, const float player_height, const float reset_x);


    private:
        sf::Vector2f position;
        sf::CircleShape image;
        sf::Vector2f direction;
        float speed;
};

#endif