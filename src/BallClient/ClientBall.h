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
    struct Message {
        int type;      
        float x;      
        float y;
        int id;   
        const char* message;
    };


    void Initialize();
    static DWORD WINAPI ReceiveDataThread(LPVOID lpParameter);
    void SendData(const Message& msg);
    void ReceiveData();
    char* GetBuffer();
    SOCKET getSocket();
    int op;
    unsigned int xx;
    float y;

private:
    SOCKET ClientSocket;
    sockaddr_in serverAddr;
  //  char buffer[1400];
};
