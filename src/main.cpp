#include <iostream>
#include "NavalBattle.h"
#include "Client.h"

#define		PORT 1111			// Defini��o da porta padr�o
#define		BUFFER_SIZE 50		// Defini��o do tamanho do buffer das mensagens

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "portuguese");
	setlocale(LC_ALL, "en_US");

	Client client;
	client.StartClient();

	//NavalBattle navalBattle;

	//navalBattle.printBoard();
	
	//client.SetGame();
	//navalBattle.Run();





	system("PAUSE");
	return 0;
}
