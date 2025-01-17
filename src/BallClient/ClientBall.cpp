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
        std::cerr << "Erreur lors de la cr�ation du socket: " << WSAGetLastError() << std::endl;
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
        std::cerr << "Erreur lors de la cr�ation du thread" << std::endl;
        exit(1);
    }
}

void ClientBall::SendData(const char* message) {
    int ret = sendto(ClientSocket, message, strlen(message), 0,
        reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr));
    if (ret == -1) {
        std::cerr << "Erreur d'envoi de donn�es client." << std::endl;
        exit(1);
    }
}

void ClientBall::ReceiveData(int id) {
    if (ClientSocket == INVALID_SOCKET) {
        std::cerr << "Erreur : le socket client est invalide.\n";
        return;
    }


    sockaddr_in senderAddr;
    socklen_t senderAddrLen = sizeof(senderAddr);

    char buffer[1400];
    int ret = recvfrom(ClientSocket, buffer, sizeof(buffer) - 1, 0, reinterpret_cast<sockaddr*>(&senderAddr), &senderAddrLen);
    if (ret == SOCKET_ERROR) {
        std::cerr << "Erreur de r�ception client: " << WSAGetLastError() << std::endl;
    }
    else {
        switch(id)
        {
        case -1:
            break;
        case 0:
            buffer[ret] = '\0';
            //memcpy(&x, buffer, sizeof(x));
            memcpy(&xx, buffer, sizeof(xx));
            break;
        case 1:
            buffer[ret] = '\0';
            memcpy(&y, buffer, sizeof(y));
            break;
        }
        serverAddr = senderAddr;
        std::cout << "client: " << xx << std::endl;
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
            std::cerr << "Erreur : le socket client n'est pas valide dans le thread de r�ception.\n";
            break;
        }

        clientBall->ReceiveData(1);
        //Sleep(100);
    }

    return 0;
}

