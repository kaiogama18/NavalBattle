#include "NavalBattle.h"
#include "Server.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "portuguese");
	setlocale(LC_ALL, "en_US");

	Server server;
	server.JoinServer();
	//NavalBattle navalBattle;
	return 0;
}
