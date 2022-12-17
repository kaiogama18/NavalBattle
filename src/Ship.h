#pragma once
#include<string>

class Ship
{
public:
	Ship(const int&,
		std::string,
		int, int, char);

	const int& GetId() const;
	const std::string& GetName() const;
	const int GetQuantity() const;
	const int& GetSpace() const;
	const char& GetIcon() const;
	
	//const int& GetTotalShip() const;
	//const void SetTotalShip(int);

	const void SetQuantity(int);

private:
	const int ID;
	std::string m_Name;
	int m_Quantity;
	int m_Space;
	char m_Icon;

	//int m_TotalShip;
};