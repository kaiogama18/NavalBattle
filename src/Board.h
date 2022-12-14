#pragma once

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <mutex>
#include <condition_variable>

#include "Utils.h"

class Board
{
public:

	char  griadBoard[Utils::GRID_SIZE][Utils::GRID_SIZE] =
	{
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

	};
	

	void PrintBoard();
private:
	int UniqueMultiplayerID{12321};
	std::mutex methodLock;
	int N, M;
	bool** board;
};