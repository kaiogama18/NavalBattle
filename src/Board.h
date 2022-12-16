#pragma once

#include <iostream>
#include <vector>

#include "Utils.h"
#include "Ship.h"


class Board
{
public:
	Board();
	void PrintBoard();
	void AddShip();
	void SetShip(const int &, char &);
	int GetTotalHit();

private:
	int m_Total_Hit;
	char m_Board[Utils::GRID_SIZE][Utils::GRID_SIZE];
	std::vector<Ship> m_Ships;
	std::pair<int, int> m_Coordinates;
};