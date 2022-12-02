#include <SFML/Graphics.hpp>
#include <iostream>
#include "util.h"
#include "gameManager.h"


int main(int argc, char const *argv[])
{
    int width{800};
    int height{600};
    sf::RenderWindow window(sf::VideoMode(width, height), "Pong in C++!");


    // Config
    int player_offset{55};
    int player_width{15};
    int player_height{80};
    float player_thickness{1.5f};
    float ball_radius{5.0f};
    float ball_thickness{1.5f};
    float default_player_spd{450.0f};
    float default_ball_spd{500.0f};
    //

    sf::Clock clock;
    float last = clock.getElapsedTime().asSeconds();
    float sum{0};
    int timing {40};
    int cnt{0};

    sf::Font font {sf::Font()};
    font.loadFromFile("arcadeclassic.ttf");

    PongManager manager(window, player_offset, player_width, player_height,
                        player_thickness, ball_radius, ball_thickness, default_player_spd, default_ball_spd,
                        font, 30, sf::Vector2f(width / 2, 30));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear();
        manager.tick();
        manager.render();
        window.display();

        // FPS
        sum += clock.getElapsedTime().asSeconds() - last;
        last = clock.getElapsedTime().asSeconds();
        cnt++;
        // if(cnt == timing){
        //     std::cout << 1 / (sum / cnt) << std::endl;
        //     cnt = 0;
        //     sum = 0;
        // }
        
    }

    return 0;
}