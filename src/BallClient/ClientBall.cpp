#include "ClientBall.h"

void ClientBall::Initialize() {
    // Cr�ation du socket UDP
    ClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (ClientSocket == -1) {
        std::cout << "Erreur de cr�ation du socket" << std::endl;
        exit(1);
    }


    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    HANDLE thread2 = CreateThread(
        nullptr,
        0,
        ReceiveDataThread,
        this,
        0,
        nullptr);

    if (thread2 == NULL) {
        std::cout << "Erreur lors de la cr�ation du thread de r�ception" << std::endl;
        exit(1);
    }
}

void ClientBall::SendData(const char* message) {
    int ret = sendto(ClientSocket, message, strlen(message), 0, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr));
    if (ret == -1) {
        std::cout << "Erreur d'envoi de donn�es." << std::endl;
        exit(1);
    }
}

void ClientBall::ReceiveData() {
    socklen_t addrLen = sizeof(serverAddr);
    int ret = recvfrom(ClientSocket, buffer, sizeof(buffer) - 1, 0, reinterpret_cast<sockaddr*>(&serverAddr), &addrLen);

    if (ret == -1) {
        std::cout << "Erreur de r�ception des donn�es." << std::endl;
        exit(1);
    }
    else if (ret == 0)
    {
        buffer[ret] = '\0';
        std::cout << "Message re�u : " << buffer << std::endl;
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

    clientBall->ReceiveData();

    return 0;
}