#include "stdafx.h"
#pragma comment(lib,"ws2_32.lib")
#include<winsock2.h>
#include<iostream>

#pragma warning(disable: 4996)

int main(int argc, char* argv[])
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

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));

	listen(sListen, SOMAXCONN);
	listen(sListen, 3);

	SOCKET newConnection;
	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

	if (newConnection == 0)
	{
		std::cout << "Error #2\n";
	}
	else
	{
		std::cout << "Client Connected! \n";
	}
	system("PAUSE");
	return 0;

}

