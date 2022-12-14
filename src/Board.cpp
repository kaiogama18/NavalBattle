#include "Board.h"
#include "Utils.h"

void Board::PrintBoard()
{

	for (int i = 0; i < Utils::GRID_SIZE; ++i)
	{
		std::cout << '\n';
		for (int j = 0; j < Utils::GRID_SIZE; ++j)
		{
			std::cout << griadBoard[i][j] << ' ';
		}
	}

	std::cout << "\n      SUA FROTA \n";

}
