#include<iostream>
#include "NavalBattle.h"
#include "Board.h"
#include "Server.h"
#include "Player.h"


NavalBattle::NavalBattle()
{
	std::cout << "\n ----- [ NavalBattle::NavalBattle() ] ----- \n\n";
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
};

void NavalBattle::Run()
{
	std::cout << '\n' << " NavalBattle::Run()" << '\n';
	
	Board board;
	Player* player1 = new Player();
	Player* player2 = new Player();

	board.PrintBoard(*player1->gridBoard);

	//player1->MyBoard(board);
	
	//player1->enterShips();

	//board.PrintBoard();
	
	//gotoxy(0, 25);
	//board.PrintBoard();
	system("PAUSE");

}



