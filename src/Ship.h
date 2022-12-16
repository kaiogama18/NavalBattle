#pragma once

#include<string>

class Ship
{
public:
	//Ship(const int&, std::string, char, char);
	Ship(const int&, std::string , int, int, char);
	
	const int ID;
	std::string m_Name;
	int m_Space;
	int m_Quantity;
	char m_Icon;
};

	//void AddShip(const std::string&, const int&, const int&);