#include <iostream>
#include "NavalBattle.h"
#include "Client.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "portuguese");
	setlocale(LC_ALL, "en_US");

	Client client;

	client.StartClient();
	//NavalBattle navalBattle;
	//navalBattle.Run();
	system("PAUSE");
	return 0;
}
