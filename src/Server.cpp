#include "Server.h"
#include "stdafx.h"
#pragma comment(lib,"ws2_32.lib")
#include<winsock2.h>
#include<iostream>

#pragma warning(disable: 4996)

Server::Server() {};

int Server::JoinServer()
{
	WSADATA wsadata;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsadata) != 0)
	{
		std::cout << "Error" << '\n';
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)))
	{
		std::cout << "Error: Failed connect to server. \n";
		return 1;
	}
	std::cout << "Connected!\n";

	char msg[256]{};
	recv(Connection, msg, sizeof(msg), NULL);
	std::cout << msg << '\n';

	system("PAUSE");
	return 0;

}

