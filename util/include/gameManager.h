#ifndef _GAMEMNG_H
#define _GAMEMNG_H

#include <SFML/Graphics.hpp>
#include "paddle.h"
#include "ball.h"


class PongManager{

    public:
        PongManager(sf::RenderWindow& window, const int player_offset,
                    const int player_width, const int player_height, const float player_thickness,
                    const float ball_radius,const float ball_thickness,
                    const float default_player_spd, const float default_ball_spd, const sf::Font& font_file,
                    const unsigned int font_size, const sf::Vector2f& score_position);

        void setup();
        void render();
        void tick();

    private:
        sf::RenderWindow& screen;
        sf::Clock clock;
        Player leftpl;
        Player rightpl;
        Ball ball;
        int window_width;
        int window_height;
        int player_xoffset;
        int player_width;
        int player_height;
        float player_thickness;
        float ball_radius;
        float ball_thickness;
        float default_player_spd;
        float default_ball_spd;
        int last_update;
        
        int right_score;
        int left_score;
        sf::Font font;
        sf::Text score_text;
        const sf::Vector2f score_pos;

        
};



#endif