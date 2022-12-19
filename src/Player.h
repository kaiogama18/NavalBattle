#pragma once

#include <vector>

#include "Board.h"
#include "Ship.h"
#include "Utils.h"

// ESTRUTURAS //
class Player
{
public:
	Player();

	void	PrintBoard();
	void	AddShip(int&);
	void	SetHealth();
	int		GetHealth();

	~Player();
private:
	Board*	m_Board;
	int		m_Health;

};

