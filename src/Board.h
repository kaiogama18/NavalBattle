#pragma once

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <mutex>
#include <condition_variable>


class Board
{
public:
	void PrintBoard(char*);
	//~Board();

private:
	std::mutex methodLock;
	int N, M;
	bool** board;
};