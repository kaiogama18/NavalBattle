#include "Server.h"


#include<winsock2.h>
#include<WS2tcpip.h>
#include <tchar.h>
#include<iostream>

//DECLARATIONS
	//error trapping signals
#define SIGINT 2
#define SIGKILL 9
#define SIGQUIT 3
//SOCKETS
SOCKET sock, client;

Server::Server() {};

int Server::JoinServer()
{
	// -------------------------------------------- Step 1 - Set up DLL 
	//std::cout << "\n===== Step 1 - Set up DLL" << "\n\n";
	SOCKET clientSocket;
	int port = 55555;
	WSADATA wsaData;
	int wsaerr;

	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);

	if (wsaerr != 0)
	{
		std::cout << "The Winsock dll not found" << '\n';
		return 0;
	}
	else
	{
		std::cout << "The Winsock dll found!" << '\n';
		std::cout << "Status: " << wsaData.szSystemStatus << '\n';
	}


	// -------------------------------------------- Step 2 - Set up Server Socket  
	//std::cout << "\n===== Step 2 - Set up Server Socket" << "\n\n";
	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (clientSocket == INVALID_SOCKET)
	{
		std::cout << "Error at socket(): " << WSAGetLastError() << '\n';
		WSACleanup;
		return 0;
	}
	else
	{
		std::cout << "socket() is OK!" << '\n';
	}

	// -------------------------------------------- Step 3 - Connect with Server 
	std::cout << "\n===== Step 3 - Connect with Server " << "\n\n";

	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);

	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
	{
		std::cout << "Client: connect() - Failed to connect " << WSAGetLastError() << '\n';
		WSACleanup();
		return 0;
	}
	else
	{
		std::cout << "Client: connect() is OK" << '\n';
		std::cout << "Client: Cand start sending and receiving data..." << '\n';
		return 1;
	}
	system("pause");
	WSACleanup();


}

