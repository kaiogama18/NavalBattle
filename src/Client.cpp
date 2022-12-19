#include "Client.h"

#include <iostream>
#include <thread>
#include <string>
#include <WinSock2.h>

#pragma comment (lib, "ws2_32.lib")


Client::Client()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		OutputData("WSAStartup failed");
		return;
	}
	OutputData("WSAStartup successfull");

	auto clientSoc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSoc == INVALID_SOCKET)
	{
		OutputData("Socket creation failed");
		CleanUp(clientSoc);
		return;
	}
	OutputData("Socket creation successfull");

	// fill server address
	struct sockaddr_in TCPServerAdd;
	TCPServerAdd.sin_family = AF_INET;
	TCPServerAdd.sin_port = htons(8000);
	TCPServerAdd.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	// connect to server
	auto iConnect = connect(clientSoc, (SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
	if (iConnect == SOCKET_ERROR)
	{
		OutputData("connect failed");
		CleanUp(clientSoc);
		return;
	}
	OutputData("Connect successfull");

	std::cout << "How do we call you, Your name please!";
	std::getline(std::cin, g_name);
	std::cout << "\n";

	auto iSend = send(clientSoc, g_name.c_str(), strlen(g_name.c_str()), 0);
	if (iSend == SOCKET_ERROR)
	{
		std::cout << "Sending Failed " << "\n";
		std::cout << "Error No-> " << WSAGetLastError() << "\n";
		CleanUp(clientSoc);
		return;
	}

	std::thread senderThread = std::thread(&send_handle, clientSoc);
	senderThread.detach();

	std::thread recverThread = std::thread(&recv_handle, clientSoc);
	recverThread.join();

	CleanUp(clientSoc);
}








void Client::OutputData(std::string message)
{
	std::cout << message << "\n";
}

void Client::CleanUp(SOCKET soc)
{
	closesocket(soc);
	WSACleanup();
}

void * Client::send_handle(SOCKET soc)
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
				CleanUp(soc);
				std::getchar();
				return;
			}
		}
	} while (data.size() > 0);
}

void * Client::recv_handle(SOCKET soc)
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
			std::cout << g_name << ": ";
		}
		else if (iRecv == 0)
		{
			std::cout << "Connection closed" << "\n";
			return;
		}
		else
		{
			std::cout << "recv failed: " << WSAGetLastError() << "\n";
			CleanUp(soc);
			std::getchar();
			return;
		}
	}
}

