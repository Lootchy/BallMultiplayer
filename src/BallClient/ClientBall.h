// ClientBall.h
#define _WINSOCKAPI_
#include <iostream>
#include <string>
#ifdef _WIN32
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SOCKET int
#define INVALID_SOCKET ((int)-1)
#endif

class ClientBall {
public:
    void Initialize();
    static DWORD WINAPI ReceiveDataThread(LPVOID lpParameter);
    void SendData(const char* message);
    void ReceiveData();
    char* GetBuffer();
    SOCKET getSocket();

private:
    SOCKET ClientSocket;
    sockaddr_in serverAddr;
    char buffer[1500];
};
