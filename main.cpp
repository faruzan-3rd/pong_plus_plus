#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "util.h"
#include "gameManager.h"


int main(int argc, char const *argv[])
{
    int width{800};
    int height{600};
    sf::RenderWindow window(sf::VideoMode(width, height), "Pong in C++!");

    const char mainmenu{'m'}, single{'s'}, multi{'l'};

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

    char current_state{mainmenu};

    PongManager manager(window, player_offset, player_width, player_height,
                        player_thickness, ball_radius, ball_thickness, default_player_spd, default_ball_spd,
                        font, 30, sf::Vector2f(width / 2, 30));

    // Main menu stuff
    sf::Text title("The pong game", font, 35);
    title.setPosition(sf::Vector2f(width / 2 - 100, 50));
    
    sf::Text singleplayer_lbl("Single player", font, 20);
    singleplayer_lbl.setPosition(sf::Vector2f(width / 2 - 50, 250));

    sf::Text multiplayer_lbl("Multi player", font, 20);
    multiplayer_lbl.setPosition(sf::Vector2f(width / 2 - 50, 300));

    int choice_index{0}, choice_size{2};
    int y_list[] = {270, 320};
    sf::ConvexShape choice_triangle(3);
    bool last_up_pressed{false}, last_down_pressed{false};
    choice_triangle.setPoint(0, sf::Vector2f(0, 10));
    choice_triangle.setPoint(1, sf::Vector2f(0, -10));
    choice_triangle.setPoint(2, sf::Vector2f(10, 0));
    choice_triangle.setPosition(sf::Vector2f(width / 2 - 75, y_list[choice_index]));


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
        if(current_state == mainmenu){
            // Arrow movement
            if(!last_up_pressed && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))){
                last_up_pressed = true;
                choice_index = (choice_index + 1) % choice_size;
            }
            if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))){
                last_up_pressed = false;
            }
            
            if(!last_down_pressed && (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))){
                last_down_pressed = true;
                choice_index = (choice_index - 1 + choice_size) % choice_size;
            }
            if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))){
                last_down_pressed = false;
            }
            // =======

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                if(choice_index == 0){
                    current_state = single;
                }else if(choice_index == 1){
                    sf::TcpSocket socket;
                    std::ifstream ifs;
                    std::string line;
                    std::string ip;
                    int port{-1};
                    std::vector<std::string> input(0);
                    ifs.open("multiplay_cfg.txt");
                    while (getline(ifs, line)) {
                        if(line.ends_with('\n')) line.erase(line.end() - 1);
                        input.push_back(line);
                    }
                    if(input.size() < 2){
                        std::cout << "Error in cfg file." << std::endl;
                        continue;
                    }
                    ip = input[0]; port = std::stoi(input[1]);

                    socket.connect(ip, port);
                    std::string msg{"ping"};
                    socket.send(msg.c_str(), msg.size() + 1);
                    char buffer[1024];
                    std::size_t received = 0;
                    socket.receive(buffer, sizeof(buffer), received);
                    std::cout << "The server said: " << buffer << std::endl;
                }
            }

            choice_triangle.setPosition(sf::Vector2f(width / 2 - 75, y_list[choice_index]));
            window.draw(title);
            window.draw(singleplayer_lbl);
            window.draw(multiplayer_lbl);
            window.draw(choice_triangle);
        }
        else if(current_state == single){
            manager.tick();
            manager.render();
        }

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