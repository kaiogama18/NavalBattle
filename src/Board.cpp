#include "Board.h"
#include <windows.h>
#include "Utils.h"

void gotoxy(int x, int y)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

void Board::PrintBoard(char arrBoard[][Utils::GRID_SIZE])
{
	int id = 1;
	for (int i = 0; i < Utils::GRID_SIZE; ++i)
	{
		std::cout << '\n';
		for (int j = 0; j < Utils::GRID_SIZE; ++j)
		{
			std::cout << arrBoard[i][j] << ' ';
		}
	}
	if (id == 1)
	{
		std::cout << "\n	SUA FROTA \n";
	}
	else
	{
		std::cout << "\n	SUA INIMIGA \n";
	}
}
