#include<iostream>
#include "NavalBattle.h"
#include "Board.h"
#include "Server.h"
#include "Player.h"
#include "AddShip.h"


NavalBattle::NavalBattle()
{
	std::cout << "\n ----- [ BATALHA NAVAL ] ----- \n";

	/*
	long currentTime = static_cast<long>(time(NULL));
	Server server;
	int socketForClient = server.WaitForPlayerToJoin();
	if (socketForClient == 0)
	{
		std::cout << "Sending seed nr for rnd: " << currentTime << '\n';
		Run();
	} 
	else
	{
		std::cout << '\n' << "[socketForClient] Player joined at socket : "
			<< socketForClient << '\n';
	}
	*/
	Run();
};

void NavalBattle::Run()
{
	//std::cout << '\n' << " NavalBattle::Run()" << '\n';

	Board board;
	Player* player1 = new Player();
	Player* player2 = new Player();
	
	/*
	player1->setId(1);
	player2->setId(2);
	board.PrintBoard(player1->getId(), player1->griadBoard);
	board.PrintBoard(player2->getId(), player1->griadBoard);
	*/

	//player1->PrintBoard();
	//player1->AddShip();
	AddShip::AddShip(player1->griadBoard);
	//gotoxy(0, 25);
	//board.PrintBoard();
	system("PAUSE");

}



