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
	
	const void SetTotalHit(int);
	const int GetTotalHit();
	
	const void SetTotalShip(int);
	const int GetTotalShip();

private:
	int m_TotalHit;
	int m_TotalShip;
	char m_Board[Utils::GRID_SIZE][Utils::GRID_SIZE];
	std::vector<Ship> m_Ships;
	std::pair<int, int> m_Coordinates;
};