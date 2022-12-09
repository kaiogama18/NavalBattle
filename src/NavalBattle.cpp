#include<iostream>
#include "NavalBattle.h"
#include "Board.h"
#include "Server.h"


NavalBattle::NavalBattle()
{
	std::cout << "\n ----- [ NavalBattle::NavalBattle() ] ----- \n\n";
	
	long currentTime = static_cast<long>(time(NULL));
	Server server;

	//std::cout << "\n ----- Esperando o Adversário chegar!" << '\n';
	int socketForClient = server.WaitForPlayerToJoin();


	std::cout << '\n' << "[socketForClient] Player joined at socket : " << socketForClient << '\n';
	std::cout << "Sending seed nr for rnd: " << currentTime << '\n';


	//Board board;
	//board.PrintBoard();
};

void NavalBattle::Run()
{
	Board board;
	board.PrintBoard();
	//gotoxy(0, 25);
	board.PrintBoard();
	system("PAUSE");

}



