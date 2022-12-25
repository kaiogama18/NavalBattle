#pragma once
#include"Player.h"


#include <iostream>
#include <thread>
#include <string>
#include <WinSock2.h>

#pragma comment (lib, "ws2_32.lib")

class Client
{
public:
	Client();
	void StartClient();
	const void Client::Menu();

private:
	Player* m_Player;
};