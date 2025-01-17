#define _WINSOCKAPI_
#include <iostream>
#include <SFML/Graphics.hpp>
#include "main.h"
#include "ServerBall.h"

int main()
{
    WSADATA data;
    WSAStartup(MAKEWORD(2, 2), &data);
    ServerBall server;
    server.Initialize();

    std::cout << "BallServer Launch " << std::endl;
    float radius = 20.0f;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Server Window");
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::Green);
    float x = 0.1;
    float y = 0.1;

    while (window.isOpen())
    {

        char buf[10];
        shape.setPosition(shape.getPosition().x + x, shape.getPosition().y + y);
        if (shape.getPosition().x < 0 || shape.getPosition().x > 800 - radius) {
            x *= -1;
        }
        else if (shape.getPosition().y < 0 || shape.getPosition().y > 600 - radius) {
            y *= -1;
        }
        unsigned int posX = (int)shape.getPosition().x;
        std::cout << "::" << posX << std::endl;
        memcpy(buf, &posX, 4);
        ServerBall::Message msg;
        msg.type = 1;
        msg.x = shape.getPosition().x;
        msg.y = shape.getPosition().y;
        server.SendData(msg);

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

    WSACleanup();
    return 0;
}