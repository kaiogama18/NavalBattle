
#include <iostream>
#include "Server.h"
#include "Player.h"
#include"NavalBattle.h"
#include"Server.h"
#include "AddShip.h"
#include "Board.h"


//UniqueMultiplayerID
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "portuguese");
	setlocale(LC_ALL, "en_US");

	/*
	Server server;
	int socketForClient = server.JoinServer();

	if (socketForClient == 1)
	{
		system("pause");
		system("CLS");
		NavalBattle navalBattle;
	}
	*/
	//NavalBattle navalBattle;
	
	Player* player1 = new Player();
	
	Board* board = new Board();

	/*
	Ship ship;
	ship.AddShip("Submarinos", 2, 3);
	ship.AddShip("Contratorpedeiros", 3, 1);
	ship.AddShip("Navio-Tanque", 4, 1);
	ship.AddShip("Porta-Avião", 5, 1);
	*/

	board->PrintBoard();

	//AddShip::AddShip(&board->griadBoard);

	board->PrintBoard();


	return 0;
}