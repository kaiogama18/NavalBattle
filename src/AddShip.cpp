#include<iostream>

#include "AddShip.h"
#include "Utils.h"

AddShip::AddShip(char griadBoard[][Utils::GRID_SIZE])
{
	int id_ship{};
	char aligned{};
	std::pair<int, int> intCoordinates;

	std::cout << "\n Coloque seus navios em campo! \n";

	for (int i = 0; i < Utils::GRID_SIZE; ++i)
	{
		std::cout << '\n';
		for (int j = 0; j < Utils::GRID_SIZE; ++j)
		{
			if (i != 0 && j != 0)
			{
				if (i == 10)
				{
					std::cout << '[' << i << ',' << j << " ]" << ' ';
				}
				else
				{
					std::cout << "[ " << i << "," << j << " ]" << ' ';

				}

			}
			else
			{
				std::cout << "    " << griadBoard[i][j] << "   ";
			}
		}
	}
	std::cout << "\n \n" << (R"( Voc� AINDA possui:

	3x Submarinos		[ 2 Quadrados ] --> ID: 1
	2x Contratorpedeiros	[ 3 Quadrados ] --> ID: 2
	1x Navio-Tanque		[ 4 Quadrados ] --> ID: 3
	1x Porta-Avi�o		[ 5 Quadrados ] --> ID: 4
	 )");

	std::cout << "\n Deseja adicionar qual navio?" << '\n';
	std::cout << "\n Informe o ID do Navio: ";
	std::cin >> id_ship;

	std::cout << " Informe as COORDENADAS iniciais: ";
	std::cin >> intCoordinates.first;
	std::cin >> intCoordinates.second;

	std::cout << " Alinhar o navio na [ VERTICAL - HORIZONTAL ]: ";
	std::cin >> aligned;
	aligned = tolower(aligned);

	SetShip(id_ship, intCoordinates, aligned);
}

void AddShip::SetShip(int id_ship, std::pair<int, int> intCoordinates, char aligned)
{
	std::cout << id_ship << aligned << intCoordinates.first << intCoordinates.second;

	for (int i = 0; i < Utils::GRID_SIZE; ++i)
	{
		for (int j = 0; j < Utils::GRID_SIZE; ++j)
		{
			if (intCoordinates.first == i && intCoordinates.second == j)
			{
				if (aligned == 'h')
				{
					griadBoard[i][j] = '2';
					griadBoard[i][j+1] = '2';
				}

			}


		}
	}
	std::cout << "\n Navio adicionado com sucesso! \n";
	Player::PrintBoard();
}
