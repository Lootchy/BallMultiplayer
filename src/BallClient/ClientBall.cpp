// ClientBall.cpp
#include "ClientBall.h"

void ClientBall::Initialize() {
    ClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (ClientSocket == INVALID_SOCKET) {
        std::cerr << "Erreur de création du socket" << std::endl;
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    HANDLE thread = CreateThread(
        nullptr, 0, ReceiveDataThread, this, 0, nullptr);

    if (thread == NULL) {
        std::cerr << "Erreur lors de la création du thread" << std::endl;
        exit(1);
    }
    CloseHandle(thread);
}

void ClientBall::SendData(const char* message) {
    int ret = sendto(ClientSocket, message, strlen(message), 0,
        reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr));
    if (ret == -1) {
        std::cerr << "Erreur d'envoi de données." << std::endl;
        exit(1);
    }
}

void ClientBall::ReceiveData() {
    std::cout << "Thread receive Client \n";
    socklen_t addrLen = sizeof(serverAddr);
    int ret = recvfrom(ClientSocket, buffer, sizeof(buffer) - 1, 0,
        reinterpret_cast<sockaddr*>(&serverAddr), &addrLen);
    if (ret == -1) {
        std::cerr << "Erreur de réception : " << WSAGetLastError() << std::endl;
    }
    else if (ret > 0) {
        buffer[ret] = '\0';
        std::cout << "Message reçu : " << buffer << std::endl;
    }
}

char* ClientBall::GetBuffer() {
    return buffer;
}

SOCKET ClientBall::getSocket() {
    return ClientSocket;
}

DWORD WINAPI ClientBall::ReceiveDataThread(LPVOID lpParameter) {
    ClientBall* clientBall = static_cast<ClientBall*>(lpParameter);
    while (true) {
        clientBall->ReceiveData();
    }
    return 0;
}
