#define _WINSOCKAPI_
#include <iostream>
#include <SFML/Graphics.hpp>
#include "main.h"
#include "ClientBall.h"

int main() {
    std::cout << "`Client\n";
    WSADATA data;
    if (WSAStartup(MAKEWORD(2, 2), &data) != 0) {
        std::cerr << "Erreur d'initialisation de WinSock" << std::endl;
        return -1;
    }

    ClientBall clientball;
    clientball.Initialize();


    closesocket(clientball.getSocket());
    WSACleanup();
    return 0;
}