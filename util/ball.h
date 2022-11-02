#ifndef _BALL_H
#define _BALL_H


#include <SFML/Graphics.hpp>


class Ball{
    public:
        Ball() = default;
        Ball(const sf::Vector2f pos, const float radius, const float thickness);

        void draw(sf::RenderWindow& window);


    private:
        sf::Vector2f position;
        sf::CircleShape image;
};

#endif