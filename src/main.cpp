#include "stdafx.h"
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma warning(disable: 4996)

#include "NavalBattle.h"

#define		PORT 1111			// Defini��o da porta padr�o
#define		BUFFER_SIZE 256		// Defini��o do tamanho do buffer das mensagens
SOCKET		Connections[100];	// Defini��o do n�mero m�ximo de clientes
int			Counter = 0;		// Auxiliar para contar o n�mero de clientes

SOCKET Connection;

enum Packet
{
	P_ChatMessage,
	//P_Test
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
	//case P_Test:
	//	std::cout << "Teste packet.\n";
	//	break;
	default:
		std::cout << "PACKET n�o reconhecido: " << packettype << std::endl;
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

	// Cria��o da estrutura do endere�o  
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(PORT);
	addr.sin_family = AF_INET;

	//Cria��o de um soquete escuta para o servidor
	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	std::cout << "Conectado ao Servidor Batalha Naval com Sucesso!\n";

	
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

	std::string msg1;
	/*
	while (true)
	{
		std::getline(std::cin, msg1);
		size_t msg_size = msg1.size();
		Packet packettype = P_ChatMessage;
		send(Connection, (char*)&packettype, sizeof(Packet), NULL);
		send(Connection, (char*)&msg_size, sizeof(int), NULL);
		send(Connection, msg1.c_str(), msg_size, NULL);
		Sleep(10);
	}
	*/

	NavalBattle navalBattle;

	navalBattle.Run();
	system("PAUSE");
	return 0;
}
