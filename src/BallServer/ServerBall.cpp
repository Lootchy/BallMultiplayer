#include "ServerBall.h"    
#include <cstring>

void ServerBall::Initialize() {
    WSADATA data;
    int result = WSAStartup(MAKEWORD(2, 2), &data);
    ServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (ServerSocket == SOCKET_ERROR) {
        std::cout << "Erreur lors de la création du socket" << std::endl;
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

    std::cout << "Serveur prêt à recevoir des données sur le port 9999..." << std::endl;

    HANDLE thread = CreateThread(
        nullptr, 0, ReceiveDataThread, this, 0, nullptr);

    if (thread == NULL) {
        std::cerr << "Erreur lors de la création du thread" << std::endl;
        exit(1);
    }

}

void ServerBall::SendData(const Message& msg) {
    int ret = sendto(ServerSocket, reinterpret_cast<const char*>(&msg), sizeof(msg), 0, reinterpret_cast<const sockaddr*>(&addrclient), sizeof(addrclient));
    if (ret == -1) {
        std::cout << "Erreur lors de l'envoi des données" << std::endl;
        exit(1);
    }
}

void ServerBall::ReceiveData() {
    sockaddr_in tempAddr;
    socklen_t fromlen = sizeof(tempAddr);

    int ret = recvfrom(ServerSocket, buffer, sizeof(buffer) - 1, 0, reinterpret_cast<sockaddr*>(&tempAddr), &fromlen);
    if (ret <= 0) {
        std::cout << "Erreur lors de la réception des données : " << WSAGetLastError() << std::endl;
    }
    else {
        buffer[ret] = '\0';
        std::cout << "Message reçu du client : " << buffer << std::endl;

        // Enregistrer l'adresse du client pour répondre plus tard.
        addrclient = tempAddr;

        Message response;
        // Envoyer une réponse au client.
        response.message = "Message reçu par le serveur !";
        SendData(response);
    }
}

char* ServerBall::GetBuffer() {
    return buffer;
}

SOCKET ServerBall::GetSocket() {
    return ServerSocket;
}


DWORD WINAPI ServerBall::ReceiveDataThread(LPVOID lpParameter) {
    ServerBall* serverBall = static_cast<ServerBall*>(lpParameter);
    while (true) {
        serverBall->ReceiveData();
    }
    return 0;
}

