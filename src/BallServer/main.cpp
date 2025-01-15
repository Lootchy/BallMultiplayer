#include <iostream>
#include <SFML/Graphics.hpp>
#include "main.h"
#include "text.h"
#include "ServerBall.h"
#ifdef _WIN32
#if _MSC_VER >= 1800
#include <WS2tcpip.h>
#else
#define inet_pton(FAMILY, IP, PTR_STRUCT_SOCKADDR) (*(PTR_STRUCT_SOCKADDR)) = inet_addr((IP))
typedef int socklen_t;
#endif
#include <WinSock2.h>
#ifdef _MSC_VER
#if _WIN32_WINNT >= _WIN32_WINNT_WINBLUE
//!< Win8.1 & higher
#pragma comment(lib, "Ws2_32.lib")
#else
#pragma comment(lib, "wsock32.lib")
#endif
#endif
#else
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in, IPPROTO_TCP
#include <arpa/inet.h> // hton*, ntoh*, inet_addr
#include <unistd.h>  // close
#include <cerrno> // errno
#define SOCKET int
#define INVALID_SOCKET ((int)-1)
#endif

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WSADATA data;
    WSAStartup(MAKEWORD(2, 2), &data);

    std::cout << "BallServer Launch " << std::endl;
    float radius = 20.0f;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::Green);
    float x = 0.1;
    float y = 0.1;

    while (window.isOpen())
    {

        shape.setPosition(shape.getPosition().x + x, shape.getPosition().y + y);
        if (shape.getPosition().x < 0 || shape.getPosition().x > 800 - radius) {
            x *= -1;
        }
        else if (shape.getPosition().y < 0 || shape.getPosition().y > 600 - radius) {
            y *= -1;
        }
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

    return 0;
}