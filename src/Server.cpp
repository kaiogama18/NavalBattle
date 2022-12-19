#include <iostream>
#include <thread>
#include <string>
#include <WinSock2.h>

#pragma comment (lib, "ws2_32.lib")
fd_set master;			



void ConnectionHandler(SOCKET connection)
{
	char nickname[50];
	ZeroMemory(nickname, 50);
	recv(connection, nickname, sizeof(nickname), 0);

	std::string welcome_message = "-----> Bem vindo ao Servidor Batalha Naval ";
	welcome_message = welcome_message + nickname;
	for (auto i = 0; i < master.fd_count; i++)
	{
		send(master.fd_array[i], welcome_message.c_str(), strlen(welcome_message.c_str()), 0);
	}
	std::cout << "\n-----> Jogador(a) ["<< master.fd_count <<"]: [ " << nickname << " ] entrou no Servidor!" << '\n';

	if (master.fd_count == 2)
	{
		
		
		//SOCKET s1 = game->getSocketOfPlayer(1);
		//SOCKET s2 = game->getSocketOfPlayer(2);

		//std::string player1;
		//std::string player2;
		


	}

	while (true)
	{
		char recvbuf[512];
		ZeroMemory(recvbuf, 512);

		auto iRecv = recv(connection, recvbuf, sizeof(recvbuf), 0);
		if (iRecv > 0)
		{
			std::cout << recvbuf << '\n';
			for (int i = 0; i < master.fd_count; i++)
			{
				if (master.fd_array[i] != connection)
					send(master.fd_array[i], recvbuf, strlen(recvbuf), 0);
			}
		}
		else if (iRecv == 0)
		{
			FD_CLR(connection, &master);
			std::cout << "A client disconnected" << '\n';
			for (int i = 0; i < master.fd_count; i++)
			{
				char disconnected_message[] = "Server : A client disconnected";
				send(master.fd_array[i], disconnected_message, strlen(disconnected_message), 0);
			}
			return;
		}
		else
		{
			FD_CLR(connection, &master);
			std::cout << "a client receive failed: " << WSAGetLastError() << '\n';
			for (int i = 0; i < master.fd_count; i++)
			{
				char disconnected_message[] = "Server : A client disconnected";
				send(master.fd_array[i], disconnected_message, strlen(disconnected_message), 0);
			}
			return;
		}
	}
}

// multiple client using threads for each client
void accept_handler(SOCKET connection)
{
	while (true)
	{
		auto acceptSoc = ::accept(connection, nullptr, nullptr);
		if (acceptSoc == INVALID_SOCKET)
		{
			std::cout << "accept error: " << WSAGetLastError() << '\n';
			closesocket(acceptSoc);
		}
		else
		{
			std::thread newCon = std::thread(ConnectionHandler, acceptSoc);
			newCon.detach();
			FD_SET(acceptSoc, &master);
		}
	}
}

void StartServer()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "WSADATA ERROR : Error no winsock. " << '\n';
		return;
	}
	std::cout << " WSAStartup OK!\n";
	auto sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sListen == INVALID_SOCKET)
	{
		std::cout << " Error: Falhou na criaçãp do Socket ! \n";
		return;
	}
	std::cout << " Socket criado com sucesso! \n";
	// Criação da estrutura do endereço  
	struct sockaddr_in TCPServerAdd;
	TCPServerAdd.sin_family = AF_INET;
	TCPServerAdd.sin_port = htons(1111);
	TCPServerAdd.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	auto result = bind(sListen, (sockaddr*)&TCPServerAdd, sizeof(TCPServerAdd));
	if (result == SOCKET_ERROR)
	{
		std::cout << " Error: Listen falhou \n";
		closesocket(sListen);
		WSACleanup();
		return;
	}

	result = listen(sListen, SOMAXCONN);
	if (result == SOCKET_ERROR)
	{
		std::cout << " Error: Listen falhou \n";
		closesocket(sListen);
		WSACleanup();
		return;
	}
	std::cout << " Esperando Jogador! \n";
	std::thread acceptThread = std::thread(accept_handler, sListen);
	//acceptThread.detach();
	acceptThread.join();

	closesocket(sListen);
	WSACleanup();
}

int main()
{
	setlocale(LC_ALL, "portuguese");
	setlocale(LC_ALL, "en_US");
	std::cout << "----- Servidor: Batalha Naval -----\n\n";
	StartServer();
	system("PAUSE");
	return 0;
}