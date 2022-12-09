
#include <iostream>
#include "Server.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "portuguese");
	setlocale(LC_ALL, "en_US");

	long currentTime = static_cast<long>(time(NULL));

	Server server;
	std::cout << " ----- [Batalha Naval] \n";
	std::cout << "\n ----- Esperando o Adversário chegar!" << '\n';
	int socketForClient = server.WaitForPlayerToJoin();


	//td::cout << '\n'  << "[socketForClient] Player joined at socket : " << socketForClient << '\n';
	//std::cout << "Sending seed nr for rnd: " << currentTime << '\n';


	return 0;
}