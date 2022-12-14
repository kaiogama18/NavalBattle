#pragma once

#include "Utils.h"
#include "Player.h"

class AddShip final : public Player
{
public:
	AddShip(char* [][Utils::GRID_SIZE]);
protected:
	void SetShip(int, std::pair<int, int>, char);
};