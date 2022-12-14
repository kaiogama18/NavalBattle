#include<iostream>

#include "Player.h"


void Player::PrintBoard()
{
	if (id == 2)
	{
		std::cout << "\n -------------------- \n";
	}
	for (int i = 0; i < Utils::GRID_SIZE; ++i)
	{
		std::cout << '\n';
		for (int j = 0; j < Utils::GRID_SIZE; ++j)
		{
			std::cout << griadBoard[i][j] << ' ';
		}
	}
	std::cout << "\n      SUA FROTA \n";
	/*
	if (id == 1)
	{
		std::cout << "\n      SUA FROTA \n";
	}
	else
	{
		std::cout << "\n    FROTA INIMIGA \n";
	}
	*/

}



void Player::SetId(int newId)
{
	id = newId;
}

int Player::GetId()
{
	return id;
}


