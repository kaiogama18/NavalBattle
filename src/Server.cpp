#include <iostream>
#include <thread>
#include <string>
#include <WinSock2.h>

#pragma comment (lib, "ws2_32.lib")

fd_set master;			// Um buffer de tamanho fixo.

void connection_handler(SOCKET soc)
{
	char nickname[50];
	ZeroMemory(nickname, 50);
	recv(soc, nickname, sizeof(nickname), 0);

	std::string welcome_message = "----- Bem vindo ao Servidor Batalha Naval ";
	welcome_message = welcome_message + nickname;
	for (auto i = 0; i < master.fd_count; i++)
	{
		send(master.fd_array[i], welcome_message.c_str(), strlen(welcome_message.c_str()), 0);
	}

	std::cout << "\n-----> Jogador(a): [ " << nickname << " ] entrou no Servidor!" << '\n';

	//std::cout << '\r';
	//std::cout << nickname << " Conectado" << '\n';
	//std::cout << "Server: ";

	while (true)
	{
		char recvbuf[512];
		ZeroMemory(recvbuf, 512);

		auto iRecv = recv(soc, recvbuf, sizeof(recvbuf), 0);
		if (iRecv > 0)
		{
			//std::cout << '\r';
			std::cout << recvbuf << '\n';
			//std::cout << "Server: ";
			for (int i = 0; i < master.fd_count; i++)
			{
				if (master.fd_array[i] != soc)
					send(master.fd_array[i], recvbuf, strlen(recvbuf), 0);
			}
		}
		else if (iRecv == 0)
		{
			FD_CLR(soc, &master);
			//std::cout << '\r';
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
			FD_CLR(soc, &master);
			//std::cout << '\r';
			std::cout << "a client receive failed: " << WSAGetLastError() << '\n';
			//std::cout << "Server: ";
			// Annouce to others
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
void accept_handler(SOCKET soc)
{
	while (true)
	{
		auto acceptSoc = ::accept(soc, nullptr, nullptr);
		if (acceptSoc == INVALID_SOCKET)
		{
			//	std::cout << '\r';
			std::cout << "accept error: " << WSAGetLastError() << '\n';
			closesocket(acceptSoc);
		}
		else
		{
			std::thread newCon = std::thread(connection_handler, acceptSoc);
			newCon.detach();
			FD_SET(acceptSoc, &master);
		}
	}
}

/*
void send_handler(SOCKET soc)
{
	std::string data;

	do
	{
		std::cout << "Server: ";
		getline(std::cin, data);
		data = "Server: " + data;
		for (auto i = 0; i < master.fd_count; i++)
		{
			auto result = send(master.fd_array[i], data.c_str(), strlen(data.c_str()), 0);
			if (result == SOCKET_ERROR)
			{
				std::cout << '\r';
				std::cout << "send to client " << i << " failed: " << WSAGetLastError() << '\n';
				std::cout << "Server: ";
				return;
			}
		}
	} while (data.size() > 0);
}
*/

/*
void OutputData(std::string message)
{
	std::string msg = "\n----- Batalha Naval Online -----\n";

	std::cout << message << "\n";
}
*/

void StartServer()
{

	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "WSADATA ERROR : Error no winsock. " << '\n';
		return;
	}
	std::cout << " WSAStartup OK!\n";

	auto serverSoc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSoc == INVALID_SOCKET)
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

	auto result = bind(serverSoc, (sockaddr*)&TCPServerAdd, sizeof(TCPServerAdd));
	if (result == SOCKET_ERROR)
	{
		std::cout << " listen failed \n";
		closesocket(serverSoc);
		WSACleanup();
		return;
	}

	result = listen(serverSoc, SOMAXCONN);
	if (result == SOCKET_ERROR)
	{
		std::cout << " listen failed \n";
		closesocket(serverSoc);
		WSACleanup();
		return;
	}
	std::cout << " Esperando Jogador! \n";

	std::thread acceptThread = std::thread(accept_handler, serverSoc);
	//acceptThread.detach();
	acceptThread.join();

	//std::thread sendThread = std::thread(send_handler, serverSoc);
	//sendThread.join();

	closesocket(serverSoc);
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