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


    SendData("Client Send his Add to the server \n");
    HANDLE thread = CreateThread(
        nullptr, 0, ReceiveDataThread, this, 0, nullptr);

    if (thread == NULL) {
        std::cerr << "Erreur lors de la création du thread" << std::endl;
        exit(1);
    }
}

void ClientBall::SendData(const char* message) {
    int ret = sendto(ClientSocket, message, strlen(message), 0,
        reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr));
    if (ret == -1) {
        std::cerr << "Erreur d'envoi de données client." << std::endl;
        exit(1);
    }
}
void ClientBall::ReceiveData() {
    if (ClientSocket == INVALID_SOCKET) {
        std::cerr << "Erreur : le socket client est invalide.\n";
        return;
    }

    std::cout << "Thread receive Client has been launched.\n";

    sockaddr_in senderAddr;
    socklen_t senderAddrLen = sizeof(senderAddr);

    int ret = recvfrom(ClientSocket, buffer, sizeof(buffer) - 1, 0, reinterpret_cast<sockaddr*>(&senderAddr), &senderAddrLen);
    if (ret == SOCKET_ERROR) {
        std::cerr << "Erreur de réception client: " << WSAGetLastError() << std::endl;
    }
    else {
        buffer[ret] = '\0'; // Ajoutez une terminaison de chaîne
        std::cout << "Message reçu : " << buffer << std::endl;
        serverAddr = senderAddr;
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
        if (clientBall->getSocket() == INVALID_SOCKET) {
            std::cerr << "Erreur : le socket client n'est pas valide dans le thread de réception.\n";
            break;
        }

        clientBall->ReceiveData();
        Sleep(100);
    }

    return 0;
}

