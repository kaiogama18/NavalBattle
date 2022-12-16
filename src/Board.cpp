#include <string.h>
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
	/*
	m_Ships.push_back(Ship(1, "Submarinos", '2', '3'));
	m_Ships.push_back(Ship(2, "Contratorpedeiros", '3', '2'));
	m_Ships.push_back(Ship(3, "Navio-Tanque", '2', '1'));
	m_Ships.push_back(Ship(4, "Porta-Avião", '5', '1'));
	*/



	m_Ships.push_back(Ship(1, "Submarinos", 2, 3, '2'));
	m_Ships.push_back(Ship(2, "Contratorpedeiros", 3, 2, '3'));
	m_Ships.push_back(Ship(3, "Navio-Tanque", 4, 1,'4'));
	m_Ships.push_back(Ship(4, "Porta-Avião", 5, 1, '5'));
	
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

void Board::SetShip(const int & ID, char & aligned)
{
	int reppet{};
	for (auto aux = m_Ships.begin(); aux != m_Ships.end(); ++aux)
	{
		if (ID == aux->ID)
		{
			std::cout << "\n Adicionando: " << aux->m_Name << " (" << aux->m_Space << " quadrados)";
			std::cout << "\n Na posição: [" << m_Coordinates.first << "," << m_Coordinates.second << "]\n";
			
			if (aligned == 'h')
			{
				for (int reppet = 0; reppet < aux->m_Space; ++reppet) 
					this->m_Board[m_Coordinates.first][m_Coordinates.second + reppet] = aux->m_Icon;
			}
			
			if (aligned == 'v')
			{
				for (int reppet = 0; reppet < aux->m_Space; ++reppet)
					this->m_Board[m_Coordinates.first + reppet][m_Coordinates.second ] = aux->m_Icon;
			}
		}
	}
}

void Board::AddShip()
{
	int id_ship{};
	char aligned{};
	

	std::cout << "\n Coloque seus navios em campo! \n";

	for (int i = 0; i < Utils::GRID_SIZE; ++i)
	{
		std::cout << '\n';
		for (int j = 0; j < Utils::GRID_SIZE; ++j)
		{
			if (i != 0 && j != 0)
			{
				if (i == 10) std::cout << '[' << i << ',' << j << " ]" << ' ';
				else std::cout << "[ " << i << "," << j << " ]" << ' ';
			}
			else std::cout << "    " << m_Board[i][j] << "   ";
		}
	}
	std::cout << "\n\n Você AINDA possui:\n";

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
	std::cin >> m_Coordinates.first;
	std::cin >> m_Coordinates.second;

	std::cout << " Alinhar o navio na [ VERTICAL - HORIZONTAL ]: ";
	std::cin >> aligned;
	aligned = tolower(aligned);

	SetShip(id_ship, aligned);

		std::cout << "\n Navio adicionado com sucesso! \n";
}



