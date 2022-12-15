#pragma once

#include <thread>
#include <vector>
#include <mutex>

#include"Player.h"

class NavalBattle
{
public:
	NavalBattle();
	//void PlaceShips();
	void Run();

private:

	Player* m_Player;
	//int P, N;
	//std::mutex mtx;
	//std::vector<std::thread*>* threads = new std::vector<std::thread*>;
};