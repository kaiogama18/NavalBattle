#pragma once

#include <vector>

#include "Utils.h"
#include "Board.h"
#include "Ship.h"

class Player
{
public:
	Player();
	int m_Health;
	
	void PrintBoard();
	void AddShip(int &);
	~Player();
private:
	Board* m_Board;
	//int ID;
	//std::vector<Ship> m_Ships;
};

