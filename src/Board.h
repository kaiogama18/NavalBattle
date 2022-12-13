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
	void PrintBoard(int , char[][Utils::GRID_SIZE]);
private:
	std::mutex methodLock;
	int N, M;
	bool** board;
};