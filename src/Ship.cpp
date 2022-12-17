#include "Ship.h"
#include <iostream>

Ship::Ship(const int& id, std::string name, int  space, int  quantity, char icon)
	: ID{ id }, m_Name{ name }, m_Space{ space }, m_Quantity{ quantity }, m_Icon{ icon }
{
}

const int& Ship::GetId() const
{
	return ID;
}

const std::string& Ship::GetName() const
{
	return m_Name;
}

const int Ship::GetQuantity() const
{
	return m_Quantity;
}

const int& Ship::GetSpace() const
{
	return m_Space;
}

const char& Ship::GetIcon() const
{
	return m_Icon;
}

/*
const int& Ship::GetTotalShip() const
{
	return m_TotalShip;
}

const void Ship::SetTotalShip(int ship)
{
	m_TotalShip = m_TotalShip + ship;
}
*/

const void Ship::SetQuantity(int quantity)
{
	m_Quantity = quantity;
}