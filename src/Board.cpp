#include "Board.h"
#include <windows.h>

constexpr unsigned MAX_ROWS{ 11 };
constexpr unsigned MAX_COLS{ 11 };
char arrBoardss[MAX_ROWS][MAX_COLS] =
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

void gotoxy(int x, int y)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}
void Board::PrintBoard(char * arrBoard)
{
	int id = 1;
	for (int i = 0; i < MAX_ROWS; ++i)
	{
		std::cout << '\n';
		for (int j = 0; j < MAX_COLS; ++j)
		{
			std::cout << '-' << ' ';
			std::cout << arrBoard[i][j] << ' ';
			//std::cout << '[' <<  i << ',' << j << ']' << ' ';
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
