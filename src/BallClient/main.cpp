#define _WINSOCKAPI_
#include <iostream>
#include <SFML/Graphics.hpp>
#include "main.h"
#include "ClientBall.h"

int main() {
    std::cout << "Client\n";
    WSADATA data;
    if (WSAStartup(MAKEWORD(2, 2), &data) != 0) {
        std::cerr << "Erreur d'initialisation de WinSock" << std::endl;
        return -1;
    }

    ClientBall clientball;
    clientball.Initialize();

    std::cout << "BallServer Launch " << std::endl;
    float radius = 20.0f;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Client Window");
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
  // std::cout << "o: " << clientball.xx << std::endl;
        shape.setPosition(clientball.xx, clientball.y);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();

    }

    closesocket(clientball.getSocket());
    WSACleanup();
    return 0;
}