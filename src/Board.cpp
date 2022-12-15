#include "Board.h"
#include "Utils.h"
#include "Ship.h"

Board::Board() : m_Board{
			{' ','A','B','C','D','E','F','G','H','I','J'},
			{'1','-','-','-','-','-','-','-','-','-','-'},
			{'2','-','-','-','-','-','-','-','-','-','-'},
			{'3','-','-','-','-','-','-','-','-','-','-'},
			{'4','-','-','-','-','-','-','-','-','-','-'},
			{'5','-','-','-','-','-','-','-','-','-','-'},
			{'6','-','-','-','-','-','-','-','-','-','-'},
			{'7','-','-','-','-','-','-','-','-','-','-'},
			{'8','-','-','-','-','-','-','-','-','-','-'},
			{'9','-','-','-','-','-','-','-','-','-','-'},
			{'0','-','-','-','-','-','-','-','-','-','-'},
}
{
	m_Ships.push_back(Ship(1, "Submarinos", 2, 3));
	m_Ships.push_back(Ship(2, "Contratorpedeiros", 3, 2));
	m_Ships.push_back(Ship(3, "Navio-Tanque", 2, 1));
	m_Ships.push_back(Ship(4, "Porta-Avião", 5, 1));
	AddShip();
}

void Board::PrintBoard()
{
	for (int i = 0; i < Utils::GRID_SIZE; ++i)
	{
		std::cout << '\n';
		for (int j = 0; j < Utils::GRID_SIZE; ++j)
		{
			std::cout << m_Board[i][j] << ' ';
		}
	}
}

void Board::AddShip()
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
				std::cout << "    " << m_Board[i][j] << "   ";
			}
		}
	}
	std::cout << "\n\n Você AINDA possui:\n" ;

	
	for (auto i = m_Ships.begin(); i != m_Ships.end(); ++i)
	{
		std::cout << " [ ID: " << i->ID << " ]" << " ..............."
			<< " " << i->m_Quantity << "x "
			<< i->m_Name << " (" << i->m_Space
			<< " quadrados)" << '\n';
	}

	std::cout << "\n Deseja adicionar qual navio?" << '\n';
	std::cout << "\n Informe o ID do Navio: ";
	std::cin >> id_ship;

	std::cout << " Informe as COORDENADAS iniciais: ";
	std::cin >> intCoordinates.first;
	std::cin >> intCoordinates.second;

	std::cout << " Alinhar o navio na [ VERTICAL - HORIZONTAL ]: ";
	std::cin >> aligned;
	aligned = tolower(aligned);



	for (int i = 0; i < Utils::GRID_SIZE; ++i)
	{
		for (int j = 0; j < Utils::GRID_SIZE; ++j)
		{
			if (intCoordinates.first == i && intCoordinates.second == j)
			{
				if (m_Board[i][j] == '-')
				{
					if (aligned == 'h')
					{
						m_Board[i][j] = '2';
						m_Board[i][j + 1] = '2';
					}
					else if (aligned == 'v')
					{
						m_Board[i][j] = '2';
						m_Board[i + 1][j] = '2';
					}
				}
			}
		}
	}
	std::cout << "\n Navio adicionado com sucesso! \n";

}
