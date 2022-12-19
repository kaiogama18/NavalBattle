#include"Client.h"

#include "stdafx.h"
#pragma comment (lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>

#include <thread>
#include <string>


#define		PORT 1111			// Definição da porta padrão
#define		BUFFER_SIZE 256		// Definição do tamanho do buffer das mensagens
SOCKET		Connections[100];	// Definição do número máximo de clientes
int			Counter = 0;		// Auxiliar para contar o número de clientes
std::string g_name;

Client::Client()
{
}

void send_handle(SOCKET soc)
{
	std::string data;
	do
	{
		std::cout << g_name << " : ";
		std::getline(std::cin, data);
		if (data.size() > 0)
		{
			data = g_name + ": " + data;
			if (send(soc, data.c_str(), strlen(data.c_str()), 0) == SOCKET_ERROR)
			{
				std::cout << "send failed: " << WSAGetLastError() << "\n";
				closesocket(soc);
				WSACleanup();
				std::getchar();
				return;
			}
		}
	} while (data.size() > 0);
}

void recv_handle(SOCKET soc)
{
	while (true)
	{
		char recvbuf[512];
		ZeroMemory(recvbuf, 512);
		auto iRecv = recv(soc, recvbuf, 512, 0);
		if (iRecv > 0)
		{
			std::cout << '\r';
			std::cout << recvbuf << "\n";
			//std::cout << g_name << ": ";
		}
		else if (iRecv == 0)
		{
			std::cout << "Connection closed" << "\n";
			return;
		}
		else
		{
			std::cout << "recv failed: " << WSAGetLastError() << "\n";
			closesocket(soc);
			WSACleanup();
			std::getchar();
			return;
		}
	}
}


void Client::StartClient()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "WSADATA ERROR : Error no winsock." << "\n";
		return;
	}

	auto clientSoc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSoc == INVALID_SOCKET)
	{
		std::cout << "Error: falha na conexão ( Falha na criação do Socket )" << "\n";
		closesocket(clientSoc);
		WSACleanup();
		return;
	}

	// fill server address
	struct sockaddr_in TCPServerAdd;
	TCPServerAdd.sin_family = AF_INET;
	TCPServerAdd.sin_port = htons(PORT);
	TCPServerAdd.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	// connect to server
	auto iConnect = connect(clientSoc, (SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
	if (iConnect == SOCKET_ERROR)
	{
		std::cout << "Error: falha na conexão" << "\n";
		closesocket(clientSoc);
		WSACleanup();
		return;
	}
	std::cin.clear();
	std::cout << "-----> Conectado ao Servidor Batalha Naval!\n";
	std::cout << "\n\tInfome seu NickName: ";
	std::getline(std::cin, g_name);
	std::cout << "\n";

	auto iSend = send(clientSoc, g_name.c_str(), strlen(g_name.c_str()), 0);
	if (iSend == SOCKET_ERROR)
	{
		std::cout << "Sending Failed " << "\n";
		std::cout << "Error No-> " << WSAGetLastError() << "\n";
		closesocket(clientSoc);
		WSACleanup();
		return;
	}

	/*
	std::thread senderThread = std::thread(send_handle, clientSoc);
	senderThread.detach();
	*/

	std::thread recverThread = std::thread(recv_handle, clientSoc);
	recverThread.join();

	closesocket(clientSoc);
	WSACleanup();
}