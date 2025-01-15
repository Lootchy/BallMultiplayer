#include "ServerBall.h"
#include <Windows.h>    
#include <iostream>
#include <cstring>

void ServerBall::Initialize() {
    ServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (ServerSocket == SOCKET_ERROR) {
        std::cout << "Erreur lors de la cr�ation du socket" << std::endl;
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = INADDR_ANY;

    int res = bind(ServerSocket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    if (res == SOCKET_ERROR) {
        std::cout << "Erreur de liaison du socket au port" << std::endl;
        exit(1);
    }

    std::cout << "Serveur pr�t � recevoir des donn�es sur le port 9999..." << std::endl;
}

void ServerBall::SendData(const char* message) {
    int ret = sendto(ServerSocket, message, strlen(message), 0, reinterpret_cast<const sockaddr*>(&addrclient), sizeof(addrclient));
    if (ret == -1) {
        std::cout << "Erreur lors de l'envoi des donn�es" << std::endl;
        exit(1);
    }
}

void ServerBall::ReceiveData() {
    sockaddr_in tempAddr;
    socklen_t fromlen = sizeof(tempAddr);

    while(true)
    {
        int ret = recvfrom(ServerSocket, buffer, 1500, 0, reinterpret_cast<sockaddr*>(&tempAddr), &fromlen);
        if (ret <= 0) {
            std::cout << "Erreur lors de la r�ception des donn�es" << std::endl;
            exit(1);
        }
        else {
            buffer[ret] = '\0';
            std::cout << "Message re�u : " << buffer << std::endl;
            addrclient = tempAddr;
        }
    }
}

char* ServerBall::GetBuffer() {
    return buffer;
}

SOCKET ServerBall::GetSocket() {
    return ServerSocket;
}
