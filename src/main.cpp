#include "NavalBattle.h"
#include "ServerClient.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "portuguese");
	setlocale(LC_ALL, "en_US");

	ServerClient client;
	client.JoinServer();
	//NavalBattle navalBattle;
	return 0;
}
