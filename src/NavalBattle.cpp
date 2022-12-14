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


//	Board board;
	
	//std::cout << "\nCriando um novo jogador! \n";
	Player* player1 = new Player();
	//Player* player2 = new Player();
	AddShip::AddShip(player1->griadBoard);

}



