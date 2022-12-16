#pragma once

#include <vector>

#include "Utils.h"
#include "Board.h"
#include "Ship.h"

class Player
{
public:
	Player();
	
	void PrintBoard();
	void AddShip(int&);
	void SetHealth();
	int GetHealth();
	~Player();
private:
	Board* m_Board;
	int m_Health;
	//int ID;
	//std::vector<Ship> m_Ships;
};

