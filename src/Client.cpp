#include"Client.h"

#include "stdafx.h"
#pragma comment (lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>

#include <thread>
#include <string>

#define		PORT 1111			// Definição da porta padrão
#define		BUFFER_SIZE 512		// Definição do tamanho do buffer das mensagens
std::string g_name;

enum Packet
{
	P_Coordenadas
};


Client::Client()
{

	//Um jogador para um cliente
	m_Player = new Player;
	// Vida do jogador é a somatoria de todos os quadrados dos barcos = 21 
	m_Player->SetHealth();
	Menu();
}

// Menu para configurar seu  tabuleiro //  
const void Client::Menu()
{
	int op;
	std::string nickName;

	std::cout << "\n ----- [ MENU ]\n\n";
	std::cout << R"( 1 - Entrar no Servidor
 2 - Cadastra Navios
 3 - Imprimir o Tabuleiro
 0 - Sair )" << '\n';
	std::cout << "\n-----> Informe a opção: ";
	std::cin >> op;
	std::cin.clear();

	switch (op)
	{
	case 1:
		std::cin.ignore();
		StartClient();
		break;
	case 2:
		std::cout << "\n Cadastra Navios ";
		break;

	case 3:
		std::cout << "\n  Imprimir o Tabuleiro ";
		m_Player->PrintBoard();
		break;
	case 0:
		break;
	default:
		break;
	}

}



void SendHandle(SOCKET Connection)
{
	std::string data;
	//Packet packettype;

	do
	{
		/*
		recv(Connection, (char*)&packettype, sizeof(Packet), NULL);
		if (packettype == P_Coordenadas)
		{
			std::cout << "SendHandle -> P_Coordenadas\n";
		}
		else
		{
			std::cout << "SendHandle -> \n" << P_Coordenadas;

		}
		*/

		//std::cout << g_name << " : ";
		std::getline(std::cin, data);
		if (data.size() > 0)
		{
			//data = g_name + ": " + data;
			if (send(Connection, data.c_str(), strlen(data.c_str()), 0) == SOCKET_ERROR)
			{
				std::cout << "send failed: " << WSAGetLastError() << "\n";
				closesocket(Connection);
				WSACleanup();
				return;
			}
		}
	} while (data.size() > 0);
}

void RecvHandle(SOCKET Connection)
{
	Packet packettype;

	while (true)
	{
		recv(Connection, (char*)&packettype, sizeof(Packet), NULL);
		if (packettype == P_Coordenadas)
		{
			//std::cout << "RecvHandle -> P_Coordenadas\n";
			char buffer[BUFFER_SIZE];
			ZeroMemory(buffer, BUFFER_SIZE);
			auto bytes = recv(Connection, buffer, BUFFER_SIZE, 0);



			//m_Player->IsHit(bytes);
			//m_Player->IsHit();

			//m_Player-HitSip(recv(Connection, (char*)&recvData, sizeof(recvData), 0));

				//players = recv(Connection, (char*)&recvData, sizeof(recvData), 0);




		}
		else
		{

			char buffer[BUFFER_SIZE];
			ZeroMemory(buffer, BUFFER_SIZE);							// Zerar o buffer
			auto bytes = recv(Connection, buffer, BUFFER_SIZE, 0);		// Continua recebendo dados até mandar parar

			if (bytes > 0)
			{
				std::cout << buffer << "\n";					// Conteudo do buffer
			}
			else if (bytes == 0)
			{
				std::cout << "Connection closed" << "\n";
				return;
			}
			else
			{
				std::cout << "recv failed: " << WSAGetLastError() << "\n";
				closesocket(Connection);
				WSACleanup();
				return;
			}
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
	SOCKET clientSoc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (clientSoc == INVALID_SOCKET)
	{
		std::cout << "Error: falha na conexão ( Falha na criação do Socket )" << "\n";
		closesocket(clientSoc);
		WSACleanup();
		return;
	}

	// Criação da estrutura do endereço //
	struct sockaddr_in TCPServerAdd;								// Estrura para qual conectar
	TCPServerAdd.sin_family = AF_INET;								// Ip versão 4
	TCPServerAdd.sin_port = htons(PORT);							// Qual a porta que o servidor vai usar 
	TCPServerAdd.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");		// Identifica o endereço do servidor em bit

	// Conexão com servidor //
	auto iConnect = connect(clientSoc, (SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
	if (iConnect == SOCKET_ERROR)
	{
		std::cout << "Error: falha na conexão" << "\n";
		closesocket(clientSoc);
		WSACleanup();
		return;
	}
	std::cin.clear();

	std::cout << "\n\tInfome seu NickName: ";
	std::getline(std::cin, g_name);
	std::cout << "\n";

	auto servidor = send(clientSoc, g_name.c_str(), strlen(g_name.c_str()), 0);
	if (servidor == SOCKET_ERROR)
	{
		std::cout << "Sending Failed " << "\n";
		std::cout << "Error No-> " << WSAGetLastError() << "\n";
		closesocket(clientSoc);
		WSACleanup();
		return;
	}

	std::thread senderThread = std::thread(SendHandle, clientSoc);
	senderThread.detach();

	std::thread recverThread = std::thread(RecvHandle, clientSoc);
	recverThread.join();

	closesocket(clientSoc);
	WSACleanup();
}