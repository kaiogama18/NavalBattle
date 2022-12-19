#include "NavalBattle.h"

#include<iostream>
#include<thread>
#include "Player.h"

NavalBattle::NavalBattle()
{
	std::cout << "\n ----- [ BATALHA NAVAL ] ----- \n";
	m_Player = new Player;
	m_Player->SetHealth();
};

void NavalBattle::Run()
{
	std::pair<int, int> m_Coordinates;
	std::cout << "\n Informe as COORDENADAS para atacar: \n";
	std::cin >> m_Coordinates.first;
	std::cin >> m_Coordinates.second;


}



