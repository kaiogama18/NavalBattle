#include "NavalBattle.h"

#include<iostream>
#include "Player.h"

NavalBattle::NavalBattle()
{
	std::cout << "\n ----- [ BATALHA NAVAL ] ----- \n";
	m_Player = new Player;
	

	//m_Player->AddShip(m_Player->m_Health);
	//m_Player->PrintBoard();
	 //mainPlayer;
	//mainPlayer->PrintBoard();
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
	//Run();
};

void NavalBattle::Run()
{

	//mainPlayer->PrintBoard();
	//Board board;
	//std::cout << "\nCriando um novo jogador! \n";
	//Player* player1 = new Player();
	//Player* player2 = new Player();
	//AddShip::AddShip(player1->griadBoard);

}



