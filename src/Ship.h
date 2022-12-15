#pragma once

#include<string>

class Ship
{
public:
	Ship(const int&, std::string,  int,  int);
	
	const int ID;
	std::string m_Name;
	int m_Space;
	int m_Quantity;
};

	//void AddShip(const std::string&, const int&, const int&);