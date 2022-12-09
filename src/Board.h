#pragma once

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <mutex>
#include <condition_variable>


const int rows = 10;
const int elements = 10;
//int matrix[rows][elements];





class Board
{
public:
	Board();
	void PrintBoard();
	//~Board();

private:
	std::mutex methodLock;
	int N, M;
	bool** board;
};