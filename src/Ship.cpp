#include "Ship.h"


Ship::Ship()
{

}

void Ship::AddShip(const std::string& name, const int& space,  const int& quantity)
{
	if (!name.empty())
	{
		m_Name = name;
		m_Space = space;
		m_Quantity = quantity;
	}
}


/*
Ship::Ship(int qta, const int space)
	: m_Qta{ qta }
	, m_Space{ space }
{

}
*/


/*

Ship::Ship(int qta, int space)
{
	m_qta = qta;
	m_space = space;
} : m_qta{ qta }, m_space{ space }
*/