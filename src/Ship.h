#pragma once

#include<string>

class Ship
{
public:
	Ship();
	//Ship(int,  const int);
	void AddShip(const std::string&, const int&, const int&);
private:
	std::string m_Name;
	int m_Space;
	int m_Quantity;

};
