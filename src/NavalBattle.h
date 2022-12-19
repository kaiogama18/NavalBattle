#pragma once

#include <thread>
#include <vector>
#include <mutex>

#include"Player.h"
#include"Client.h"

class NavalBattle
{
public:
	NavalBattle();
	
	const void Menu();

private:
	
	Client* m_Client;
	Player* m_Player;
};