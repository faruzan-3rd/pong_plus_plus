#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <string>


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

    sf::TcpListener listener;
    listener.listen(port);
    // Wait for a connection
    sf::TcpSocket socket;
    listener.accept(socket);
    std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
    // Receive a message from the client
    char buffer[1024];

    while(1){
        std::size_t received = 0;
        socket.receive(buffer, sizeof(buffer), received);
        if(received > 0){
            std::cout << "The client said: " << buffer << std::endl;
            std::string response{"Hello world from the server!"};
            socket.send(response.c_str(), response.size() + 1);
        }
    }
    
}