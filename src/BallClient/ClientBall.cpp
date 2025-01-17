// ClientBall.cpp
#include "ClientBall.h"

void ClientBall::Initialize() {
    WSADATA data;
    int result = WSAStartup(MAKEWORD(2, 2), &data);
    if (result != 0) {
        std::cerr << "Erreur lors de l'initialisation de Winsock: " << result << std::endl;
        exit(1);
    }

    ClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (ClientSocket == INVALID_SOCKET) {
        std::cerr << "Erreur lors de la création du socket: " << WSAGetLastError() << std::endl;
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
    std::cout << "Socket ClientBall cree avec succes.\n";

    Message msg;
    msg.message = "Addresse send to the server";

    SendData(msg);
    HANDLE thread = CreateThread(
        nullptr, 0, ReceiveDataThread, this, 0, nullptr);

    if (thread == NULL) {
        std::cerr << "Erreur lors de la création du thread" << std::endl;
        exit(1);
    }
}

void ClientBall::SendData(const Message& msg) {
    int ret = sendto(ClientSocket, reinterpret_cast<const char*>(&msg), sizeof(msg), 0,
        reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr));
    if (ret == -1) {
        std::cerr << "Erreur d'envoi de données client." << std::endl;
        exit(1);
    }
}


void ClientBall::ReceiveData() {
    sockaddr_in senderAddr;
    socklen_t senderAddrLen = sizeof(senderAddr);

    char buffer[1400];
    int ret = recvfrom(ClientSocket, buffer, sizeof(buffer) - 1, 0,
        reinterpret_cast<sockaddr*>(&senderAddr), &senderAddrLen);
    if (ret <= 0) {
        std::cerr << "Erreur de réception client: " << WSAGetLastError() << std::endl;
    }
    else {
        buffer[ret] = '\0';

        Message msg;
        memcpy(&msg, buffer, sizeof(msg));
        switch (msg.type) {
        case 1:
            xx = msg.x;
            y = msg.y;
            break;
        case 2:
            break;
        default:
            break;
        }
    }
}





char* ClientBall::GetBuffer() {
    //return buffer;
    return nullptr;
}

SOCKET ClientBall::getSocket() {
    return ClientSocket;
}

DWORD WINAPI ClientBall::ReceiveDataThread(LPVOID lpParameter) {
    ClientBall* clientBall = static_cast<ClientBall*>(lpParameter);

    while (true) {
        if (clientBall->getSocket() == INVALID_SOCKET) {
            std::cerr << "Erreur : le socket client n'est pas valide dans le thread de réception.\n";
            break;
        }

        clientBall->ReceiveData();
        //Sleep(100);
    }

    return 0;
}

