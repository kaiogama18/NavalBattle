#include "stdafx.h"
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include<thread>

#include"Utils.h"
#pragma warning(disable: 4996)

#define		PORT 1111			// Definição da porta padrão
#define		BUFFER_SIZE 256		// Definição do tamanho do buffer das mensagens
SOCKET		Connections[100];	// Definição do número máximo de clientes
int			Counter = 0;		// Auxiliar para contar o número de clientes


enum Packet
{
	P_ChatMessage,
	//P_Test
};

bool ProcessPacket(int index, Packet packettype)
{
	switch (packettype)
	{
	case P_ChatMessage:
	{
		int msg_size;
		recv(Connections[index], (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connections[index], msg, msg_size, NULL);
		for (int i = 0; i < Counter; i++)
		{
			if (i == index)
			{
				continue;
			}

			Packet msgtype = P_ChatMessage;
			send(Connections[i], (char*)&msgtype, sizeof(Packet), NULL);
			send(Connections[i], (char*)&msg_size, sizeof(int), NULL);
			send(Connections[i], msg, msg_size, NULL);
		}
		delete[] msg;
		break;
	}
	default:
		std::cout << "PACKET não reconhecido: " << packettype << std::endl;
		break;
	}

	return true;
}


// Maniplidador de cliente
void ClientHandler(int index)
{
	Packet packettype;
	while (true)
	{
		recv(Connections[index], (char*)&packettype, sizeof(Packet), NULL);

		if (!ProcessPacket(index, packettype))
		{
			break;
		}
	}
	closesocket(Connections[index]);
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "portuguese");
	setlocale(LC_ALL, "en_US");

	std::cout << "----- Bem Vindo ao Servidor da Batalha Naval \n";

	// Incializando o servidor e espera pelos os jogadores[Client]
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	// Start winsock
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		std::cout << "Error" << std::endl;
		exit(1);
	}

	// Criação da estrutura do endereço  
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);

	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(PORT);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;

	std::cout << "\n \t Esperando jogador \n";


	for (int i = 0; i < 100; i++)
	{
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

		if (newConnection == 0)
		{
			std::cout << "Error #2\n";
		}
		else
		{

			std::cout << "Cliente conectado! \n";
			//char buffer[BUFFER_SIZE] = "----- Batalha Naval Online -----";
			std::string msg = "\n----- Batalha Naval Online -----\n";
			int msg_size = msg.size();
			Packet msgtype = P_ChatMessage;
			
			send(newConnection, (char*)&msgtype, sizeof(Packet), NULL);
			send(newConnection, (char*)&msg_size, sizeof(int), NULL);
			send(newConnection, msg.c_str(), msg_size, NULL);
			//send(newConnection, buffer, sizeof(buffer), NULL);

			Connections[i] = newConnection;
			Counter++;

			// Criação da Thread para execultar 2 Thread ao mesmo tempo
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
			//std::thread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
			//Packet testpacket = P_Test;
			//send(newConnection, (char*)&testpacket, sizeof(Packet), NULL);
		}
	}


	system("PAUSE");
	return 0;
}