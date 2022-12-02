#ifndef _PLY_BAR_H
#define _PLY_BAR_H


#include <SFML/Graphics.hpp>


class Player{
    public:
        Player() = default;
        Player(const sf::Vector2f& pos, const int width, const int height, const float thickness);

        void draw(sf::RenderWindow& window);
        
        sf::Vector2f get_position() const;
        void set_position(const sf::Vector2f& new_pos);
        

    private:
        sf::Vector2f position;
        int bar_height;
        int bar_width;
        sf::ConvexShape image;
    
};



#endif