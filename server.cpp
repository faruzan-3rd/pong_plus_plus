#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <string>


int assign_player(sf::TcpSocket& player1, sf::TcpSocket& player2, sf::TcpListener& listener);


int main(){
    std::ifstream ifs;
    std::string line;
    std::string ip;
    int port{-1};
    std::vector<std::string> input(0);
    ifs.open("multiplay_cfg.txt");
    while (getline(ifs, line)) {
        if(*(line.end() - 1) == '\n') line.erase(line.end() - 1);
        input.push_back(line);
    }
    if(input.size() < 2){
        std::cout << "Error in cfg file." << std::endl;
        return 0;
    }
    ip = input[0]; port = std::stoi(input[1]);

    sf::TcpListener listener1, listener2;

    sf::TcpSocket player1, player2;
    player1.setBlocking(false);
    player2.setBlocking(false);

    std::cout << "Waiting for players" << std::endl;

    if(listener1.listen(port) != sf::Socket::Done){
        std::cout << "Error 1a" << std::endl;
        listener1.close();
        return 0;
    }
    // Wait for a connection
    if(listener1.accept(player1) != sf::Socket::Done){
        std::cout << "Error 1b" << std::endl;
        listener1.close();
        return 0;
    }
    std::cout << "New client connected: " << player1.getRemoteAddress() << std::endl;


    if(listener2.listen(port) != sf::Socket::Done){
        std::cout << "Error 2a" << std::endl;
        listener2.close();
        return 0;
    }
    // Wait for a connection
    if(listener2.accept(player2) != sf::Socket::Done){
        std::cout << "Error 2b" << std::endl;
        listener2.close();
        return 0;
    }
    std::cout << "New client connected: " << player1.getRemoteAddress() << std::endl;



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


    // Receive a message from the client
    char buffer[1024];

    while(1){
        std::size_t received = 0;

        // Player1
        if(player1.receive(buffer, sizeof(buffer), received) == sf::Socket::Done){
            std::cout << "Player1 said: " << buffer << std::endl;
            std::string response{"Hello world from the server!"};
            player1.send(response.c_str(), response.size() + 1);
        }

        // Player2
        if(player2.receive(buffer, sizeof(buffer), received) == sf::Socket::Done){
            std::cout << "Player2 said: " << buffer << std::endl;
            std::string response{"Hello world from the server!"};
            player2.send(response.c_str(), response.size() + 1);
        }
    }
    
}


int assign_player(sf::TcpSocket& player1, sf::TcpSocket& player2, sf::TcpListener& listener){
    if(player1.getRemoteAddress() != sf::IpAddress::None){

        if(listener.accept(player2) == sf::Socket::Done){
            return 2;
        }else{
            return -1;
        }
    }else{
        if(listener.accept(player1) == sf::Socket::Done){
            return 1;
        }else{
            return -1;
        }
    }
}