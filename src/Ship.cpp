#include "Ship.h"

/*
Ship::Ship()
{
}
*/

Ship::Ship(const int& id, std::string name, int  space, int  quantity, char icon)
	: ID{ id }, m_Name{ name }, m_Space{ space }, m_Quantity{ quantity }, m_Icon{icon}
{

}


/*
Ship::Ship(const int* id, const std::string& name, const int& space, const int& quantity)
	: ID{ id } , m_Name{ name }, m_Space{ space }, m_Quantity{ quantity }
{
}
*/

/*
void Ship::AddShip(const std::string& name, const int& space, const int& quantity)
{
	if (!name.empty())
	{
		m_Name = name;
		m_Space = space;
		m_Quantity = quantity;
	}
}
*/


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