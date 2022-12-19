#include "stdafx.h"
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma warning(disable: 4996)

#include "NavalBattle.h"

#define		PORT 1111	
SOCKET Connection;

enum Packet
{
	P_ChatMessage,
	P_Test
};

bool ProcessPacket(Packet packettype)
{
	switch (packettype)
	{
	case P_ChatMessage:
	{
		int msg_size;
		recv(Connection, (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connection, msg, msg_size, NULL);
		std::cout << msg << std::endl;
		delete[] msg;
		break;
	}
	case P_Test:
		std::cout << "Test packet.\n";
		break;
	default:
		std::cout << "Unrecognized packet: " << packettype << std::endl;
		break;
	}

	return true;
}

void ClientHandler()
{
	Packet packettype;
	while (true)
	{
		recv(Connection, (char*)&packettype, sizeof(Packet), NULL);

		if (!ProcessPacket(packettype))
		{
			break;
		}
	}
	closesocket(Connection);
}


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "portuguese");
	setlocale(LC_ALL, "en_US");

	WSAData wsaData;
	
	WORD DLLVersion = MAKEWORD(2, 1);
	// Start winsock
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		std::cout << "WSADATA ERROR : Error no winsock." << std::endl;
		exit(1);
	}

	// Criação da estrutura do endereço  
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(PORT);
	addr.sin_family = AF_INET;

	//Criação de um soquete escuta para o servidor
	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	std::cout << "Conectado ao Servidor Batalha Naval com Sucesso!\n";

	// 
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

	std::string msg1;
	while (true)
	{
		std::getline(std::cin, msg1);
		int msg_size = msg1.size();
		Packet packettype = P_ChatMessage;
		send(Connection, (char*)&packettype, sizeof(Packet), NULL);
		send(Connection, (char*)&msg_size, sizeof(int), NULL);
		send(Connection, msg1.c_str(), msg_size, NULL);
		Sleep(10);
	}

	//NavalBattle navalBattle;
	system("PAUSE");
	return 0;
}
