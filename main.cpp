#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "util.h"
#include "gameManager.h"


const char mainmenu{'m'}, single{'s'}, multi{'l'};


void arrow_movement(std::set<sf::Keyboard::Key>& pressed, std::set<sf::Keyboard::Key>& pressed_now, int& choice_index, int& choice_size);


void connect2server(std::ifstream& ifs, std::string& ip, int& port1, int& port2, sf::UdpSocket& socket, bool& connected);


void on_enter_behaviour(std::set<sf::Keyboard::Key>& pressed, std::set<sf::Keyboard::Key>& pressed_now, int& choice_index, char& current_state, 
                         std::ifstream& ifs, std::string& ip, int& port1, int& port2, sf::UdpSocket& socket, bool& running, bool& connected);

void register_pressed_key(std::set<sf::Keyboard::Key>& pressed_now);


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

    sf::Text quit_lbl("Quit", font, 20);
    quit_lbl.setPosition(sf::Vector2f(width / 2 - 50, 350));

    int y_list[] = {265, 315, 365};
    int choice_index{0}, choice_size{3};
    sf::ConvexShape choice_triangle(3);
    bool last_up_pressed{false}, last_down_pressed{false};
    choice_triangle.setPoint(0, sf::Vector2f(0, 10));
    choice_triangle.setPoint(1, sf::Vector2f(0, -10));
    choice_triangle.setPoint(2, sf::Vector2f(10, 0));
    choice_triangle.setPosition(sf::Vector2f(width / 2 - 75, y_list[choice_index]));

    sf::UdpSocket socket;
    std::ifstream ifs;
    std::string line;
    std::string ip;
    int port1{-1};
    int port2{-1};
    bool connected{0};

    std::set<sf::Keyboard::Key> pressed;
    std::set<sf::Keyboard::Key> pressed_now;

    bool running = true;

    while (window.isOpen() && running)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear();
        pressed = pressed_now;
        pressed_now.clear();
        if(current_state == mainmenu){
            arrow_movement(pressed, pressed_now, choice_index, choice_size);

            on_enter_behaviour(pressed, pressed_now, choice_index, current_state, ifs, ip, port1, port2, socket, running, connected);

            register_pressed_key(pressed_now);
            choice_triangle.setPosition(sf::Vector2f(width / 2 - 75, y_list[choice_index]));
            window.draw(title);
            window.draw(singleplayer_lbl);
            window.draw(multiplayer_lbl);
            window.draw(quit_lbl);
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



void arrow_movement(std::set<sf::Keyboard::Key>& pressed, std::set<sf::Keyboard::Key>& pressed_now, int& choice_index, int& choice_size){
    if(utl::key_down(sf::Keyboard::Up, pressed)){
        choice_index = (choice_index - 1 + choice_size) % choice_size;   
    }
    
    if(utl::key_down(sf::Keyboard::Down, pressed)){
        choice_index = (choice_index + 1) % choice_size;
    }
}

void connect2server(std::ifstream& ifs, std::string& ip, int& port1, int& port2, sf::UdpSocket& socket, bool& connected){
    if(connected){
        return;
    }

    ifs.close();
    std::string line;
    std::vector<std::string> input(0);
    ifs.open("multiplay_cfg.txt");
    while (getline(ifs, line)) {
        if(*(line.end() - 1) == '\n') line.erase(line.end() - 1);
        input.push_back(line);
    }
    if(input.size() < 3){
        std::cout << "Error in cfg file." << std::endl;
        return;
    }
    ip = input[0]; port1 = std::stoi(input[1]); port2 = std::stoi(input[2]);
    std::cout << "Connecting to " << ip << " " << port1 << std::endl;

    char buffer[1024];
    std::string response;
    std::string msg = "connect";
    sf::IpAddress server; unsigned short sport;
    size_t received;

    socket.send(msg.c_str(), msg.size() + 1, ip, port1);
    socket.receive(buffer, sizeof(buffer), received, server, sport);
    response = std::string(buffer);

    if(server.toString() != ip){
        std::cout << "Not the actual server: " << server.toString() << std::endl;
        return;
    }

    if(response == "player1" || response == "player2"){
        connected = true;
        std::cout << response << std::endl;
    }
    else{
        std::cout << "Could not connect for some reason" << std::endl;
    }

}


void on_enter_behaviour(std::set<sf::Keyboard::Key>& pressed, std::set<sf::Keyboard::Key>& pressed_now, int& choice_index, char& current_state, 
                         std::ifstream& ifs, std::string& ip, int& port1, int& port2, sf::UdpSocket& socket, bool& running, bool& connected){
    if(!utl::key_down(sf::Keyboard::Enter, pressed)) return;

    if(choice_index == 0){
        current_state = single;

    }else if(choice_index == 1){
        connect2server(ifs, ip, port1, port2, socket, connected);
        
        std::string msg{"ping"};
        socket.send(msg.c_str(), msg.size() + 1, ip, port1);
        char buffer[1024];
        std::size_t received = 0;
        sf::IpAddress server; unsigned short sport;
        socket.receive(buffer, sizeof(buffer), received, server, sport);

        if(server != ip) return;

        std::cout << "The server said: " << buffer << std::endl;

    }else if(choice_index == 2){
        running = false;
    }
    
}

void register_pressed_key(std::set<sf::Keyboard::Key>& pressed_now){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) pressed_now.insert(sf::Keyboard::Up);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) pressed_now.insert(sf::Keyboard::Down);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) pressed_now.insert(sf::Keyboard::Enter);
}
