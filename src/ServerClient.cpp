#include "ServerClient.h"
#include "stdafx.h"
#pragma comment(lib,"ws2_32.lib")
#include<winsock2.h>
#include<iostream>
#include <string>
#pragma warning(disable: 4996)

SOCKET Connection;

void ClientHandler()
{
	char msg[256];
	int msg_size;
	while (true)
	{
		recv(Connection, (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connection, msg, msg_size, NULL);
		std::cout << msg << '\n';
		delete[] msg;
	}
}

ServerClient::ServerClient() {};

int ServerClient::JoinServer()
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

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)))
	{
		std::cout << "Error: Failed connect to server. \n";
		return 1;
	}
	std::cout << "Conectado ao Servidor Batalha Naval com Sucesso!\n";

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

	std::string msg1;
	while (true)
	{
		std::getline(std::cin, msg1);
		int msg_size = msg1.size();
		send(Connection, (char*)&msg_size, sizeof(int), NULL);
		send(Connection, msg1.c_str(), msg_size, NULL);
		Sleep(10);
	}

	system("PAUSE");
	return 0;

}

