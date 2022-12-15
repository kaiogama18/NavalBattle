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
private:
	char m_Board[Utils::GRID_SIZE][Utils::GRID_SIZE];
	std::vector<Ship> m_Ships;
};