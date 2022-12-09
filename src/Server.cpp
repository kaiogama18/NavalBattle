#include "Server.h"


#include<winsock2.h>
#include<WS2tcpip.h>
#include <tchar.h>
#include<iostream>

Server::Server() {};



int Server::WaitForPlayerToJoin()
{

	//std::cout << "\n ===== W11 Sockets";
	// -------------------------------------------- Step 1 - Set up DLL  
	//std::cout << "\n===== Step 1 - Set up DLL" << "\n\n";
	
	SOCKET serverSocket, acceptSocket;
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
	/*
	else
	{
		std::cout << "The Winsock dll found!" << '\n';
		std::cout << "Status: " << wsaData.szSystemStatus << '\n';
	}
	*/


	// -------------------------------------------- Step 2 - Set up Server Socket  
	//std::cout << "\n===== Step 2 - Set up Server Socket" << "\n\n";
	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (serverSocket == INVALID_SOCKET)
	{
		std::cout << "Error at socket(): " << WSAGetLastError() << '\n';
		WSACleanup;
		return 0;
	}
	/*
	else
	{
		std::cout << "socket() is OK!" << '\n';
	}
	*/

	// -------------------------------------------- Step 3 - Bind Socket 
	//std::cout << "\n===== Step 3 - Bind Socket" << "\n\n";
	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);

	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		std::cout << '\n' << "bind() failed:" << WSAGetLastError << '\n';
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	/*
	else
	{
		std::cout << "bind() is Ok!" << '\n';
	}
	*/


	// -------------------------------------------- Step 4 - Initiate Listen
	//std::cout << "\n===== Step 4 - Initiate Listen" << "\n\n";

	
	if (listen(serverSocket, 1) == SOCKET_ERROR)
	{
		std::cout << "listen(): Error listening on socket " << WSAGetLastError << '\n';
	}
	else
	{
		std::cout << "----- Esperando o Adversário conectar!" << '\n';
		//std::cout << "listen(): is OK, I'm waiting for connections... " << '\n';
	}

	// -------------------------------------------- Step 5 - Accept Connection
	//std::cout << "\n===== Step 5 - Accept Connection" << "\n\n";

	acceptSocket = accept(serverSocket, NULL, NULL);
	if (acceptSocket == INVALID_SOCKET)
	{
		std::cout << "Accept failed" << WSAGetLastError() << '\n';
		WSACleanup();
		return -1;

	}
	std::cout << "Accepted connection" << '\n';
	WSACleanup();

	// -------------------------------------------- Step 6
	//std::cout << "\n===== Step 6 - Chat to the client" << "\n\n";


	//char buffer[200];


	/*
	int clintListn = 0, socketForClient = 0;
	struct sockaddr_in ipOfServer;
	clintListn = socket(AF_INET, SOCK_STREAM, 0); // creating socket
	memset(&ipOfServer, '0', sizeof(ipOfServer));
	ipOfServer.sin_family = AF_INET;
	ipOfServer.sin_addr.s_addr = htonl(INADDR_ANY);
	ipOfServer.sin_port = htons(2017); // this is the port number of running server
	bind(clintListn, (struct sockaddr*)&ipOfServer, sizeof(ipOfServer));
	listen(clintListn, 1); // Start listening

	socketForClient = accept(clintListn, (struct sockaddr*)NULL, NULL);
	return socketForClient;
	*/


}
