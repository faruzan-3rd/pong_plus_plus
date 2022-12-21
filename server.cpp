#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <string>


int assign_player(sf::IpAddress& player1, sf::IpAddress& player2, const sf::IpAddress sender);


int main(){
    std::ifstream ifs;
    std::string line;
    std::string ip;
    int port1{-1}, port2{-1};
    std::vector<std::string> input(0);
    ifs.open("multiplay_cfg.txt");
    while (getline(ifs, line)) {
        if(*(line.end() - 1) == '\n') line.erase(line.end() - 1);
        input.push_back(line);
    }
    if(input.size() < 3){
        std::cout << "Error in cfg file." << std::endl;
        return 0;
    }
    ip = input[0]; port1 = std::stoi(input[1]); port2 = std::stoi(input[2]);

    sf::UdpSocket socket;
    sf::IpAddress player1 = sf::IpAddress::None, player2 = sf::IpAddress::None;

    std::cout << "Waiting for players" << std::endl;
    socket.bind(port1);
    sf::IpAddress sender; 
    unsigned short sport;
    // Receive a message from the client
    char buffer[1024];
    std::size_t received = 0;
    std::string msg;

    while(player1 == sf::IpAddress::None || player2 == sf::IpAddress::None){
        socket.receive(buffer, sizeof(buffer), received, sender, sport);
        msg = std::string(buffer);
        if(msg == "connect"){
            int code = assign_player(player1, player2, sender);
            std::string return_msg;
            if(code > 0){
                return_msg = "player" + std::to_string(code);
            }else if(code == -1){
                return_msg = "already_connected";
            }else{
                return_msg = "no";
            }
            socket.send(return_msg.c_str(), return_msg.size() + 1, sender, sport);
        }
        else if(msg == "ping"){
            std::string return_msg = "pong!";
            socket.send(return_msg.c_str(), return_msg.size() + 1, sender, sport);
        }
    }

    // if(listener1.listen(port1) != sf::Socket::Done){
    //     std::cout << "Error 1a" << std::endl;
    //     listener1.close();
    //     return 0;
    // }
    // // Wait for a connection
    // if(listener1.accept(player1) != sf::Socket::Done){
    //     std::cout << "Error 1b" << std::endl;
    //     listener1.close();
    //     return 0;
    // }
    // std::cout << "New client connected: " << player1.getRemoteAddress() << std::endl;


    // if(listener2.listen(port1) != sf::Socket::Done){
    //     std::cout << "Error 2a" << std::endl;
    //     listener2.close();
    //     return 0;
    // }
    // // Wait for a connection
    // if(listener2.accept(player2) != sf::Socket::Done){
    //     std::cout << "Error 2b" << std::endl;
    //     listener2.close();
    //     return 0;
    // }
    // std::cout << "New client connected: " << player2.getRemoteAddress() << std::endl;



    // while(player1.getRemoteAddress() == sf::IpAddress::None || player2.getRemoteAddress() == sf::IpAddress::None){
    //     if(player1.getRemoteAddress() == sf::IpAddress::None && listener1.listen(port)){
    //         std::cout << "Port listen 1" << std::endl;
    //         if(listener1.accept(player1) != sf::Socket::Done){
    //             std::cout << "Error 1" << std::endl;
    //             continue;
    //         }
    //         std::cout << "Player1 connected: " << player1.getRemoteAddress() << std::endl;
    //     }
    //     else if(player2.getRemoteAddress() == sf::IpAddress::None && listener2.listen(port)){
    //         std::cout << "Port listen 2" << std::endl;
    //         if(listener2.accept(player2) != sf::Socket::Done){
    //             std::cout << "Error 2" << std::endl;
    //             continue;
    //         }
    //         std::cout << "Player2 connected: " << player2.getRemoteAddress() << std::endl;
    //     }
    // }
    std::cout << "Both players have connected" << std::endl;

    // if(listener.listen(port) != sf::Socket::Done){
    //     std::cout << "Error" << std::endl;
    //     listener.close();
    //     return 0;
    // }
    // // Wait for a connection
    // sf::TcpSocket socket;
    // if(listener.accept(socket) != sf::Socket::Done){
    //     std::cout << "Error" << std::endl;
    //     listener.close();
    //     return 0;
    // }
    // std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;



    while(1){
        socket.receive(buffer, sizeof(buffer), received, sender, sport);
        msg = std::string(buffer);
        if(msg == "ping"){
            std::string return_msg = "pong!";
            socket.send(return_msg.c_str(), return_msg.size() + 1, sender, sport);
        }
    }
    
}


int assign_player(sf::IpAddress& player1, sf::IpAddress& player2, const sf::IpAddress sender){
    // if(player1.getRemoteAddress() != sf::IpAddress::None){

    //     if(listener.accept(player2) == sf::Socket::Done){
    //         return 2;
    //     }else{
    //         return -1;
    //     }
    // }else{
    //     if(listener.accept(player1) == sf::Socket::Done){
    //         return 1;
    //     }else{
    //         return -1;
    //     }
    // }
    if(player1 == sender || player2 == sender) return -1;
    if(player1 != sf::IpAddress::None && player2 != sf::IpAddress::None) return -2;

    if(player1 != sf::IpAddress::None){
        player2 = sender;
        return 2;
    }else{
        player1 = sender;
        return 1;
    }
}