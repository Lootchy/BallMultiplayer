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

class ServerBall {
private:
	SOCKET ServerSocket;
	sockaddr_in addr;
	sockaddr_in addrclient;
	char buffer[1400];

public:
	struct Message {
		int type;
		float x;
		float y;
		int id;
		const char* message;
	};
	void Initialize();
	void SendData(const Message& msg);
	static DWORD WINAPI ReceiveDataThread(LPVOID lpParameter);
	void ReceiveData();
	char* GetBuffer();
	SOCKET GetSocket();
};