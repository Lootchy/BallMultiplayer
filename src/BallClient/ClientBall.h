#include <iostream>
#include <string>
#include <Windows.h>  
#ifdef _WIN32
#if _MSC_VER >= 1800
#include <WS2tcpip.h>
#else
#define inet_pton(FAMILY, IP, PTR_STRUCT_SOCKADDR) (*(PTR_STRUCT_SOCKADDR)) = inet_addr((IP))
typedef int socklen_t;
#endif
#include <WinSock2.h>
#ifdef _MSC_VER
#if _WIN32_WINNT >= _WIN32_WINNT_WINBLUE
//!< Win8.1 & higher
#pragma comment(lib, "Ws2_32.lib")
#else
#pragma comment(lib, "wsock32.lib")
#endif
#endif
#else
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in, IPPROTO_TCP
#include <arpa/inet.h> // hton*, ntoh*, inet_addr
#include <unistd.h>  // close
#include <cerrno> // errno
#define SOCKET int
#define INVALID_SOCKET ((int)-1)
#endif

class ClientBall {
public:
    void Initialize();
    static DWORD WINAPI ReceiveDataThread(LPVOID lpParamter);
    void SendData(const char* message);
    void ReceiveData();
    char* GetBuffer();
    SOCKET getSocket();

private:
    int ClientSocket;
    sockaddr_in serverAddr;
    char buffer[1500];
};
