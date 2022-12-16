#include<iostream>

#include "Player.h"
#include "Ship.h"

Player::Player()
	:m_Health{}
{
	m_Board = new Board;
}

void Player::PrintBoard()
{
	m_Board->PrintBoard();
	std::cout << "\n      SUA FROTA \n";
}

void Player::AddShip(int& health)
{
	m_Board->AddShip();
}

void Player::SetHealth()
{
	m_Health = m_Board->GetTotalHit();
}

int Player::GetHealth()
{
	return m_Health;
}


Player::~Player()
{
	delete m_Board;
}