

#include<winsock2.h>
#include<WS2tcpip.h>
#include <tchar.h>
#include<iostream>



int JoinServer()
{
	int socketCreated = 0;
	struct sockaddr_in ipOfServer;
	socketCreated = socket(AF_INET, SOCK_STREAM, 0); // creating socket
	memset(&ipOfServer, '0', sizeof(ipOfServer));
	ipOfServer.sin_family = AF_INET;
	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, "127.0.0.1", &ipOfServer.sin_addr) <= 0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}
	ipOfServer.sin_port = htons(2017); // this is the port number of running server

	if (connect(socketCreated, (struct sockaddr*)&ipOfServer, sizeof(ipOfServer)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}
	return socketCreated;
}


int main(int argc, char** argv)
{

	std::cout << " ----- [Batalha Naval Client] \n";
	int socketForClient = JoinServer();
	return 0;
}