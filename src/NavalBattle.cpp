#include "NavalBattle.h"

#include<iostream>
#include "Player.h"
#include "Client.h"



NavalBattle::NavalBattle() : m_Client{}
{
	std::cout << " ----- [ BATALHA NAVAL ONLINE ] ----- \n";
	m_Player = new Player;
	m_Player->SetHealth();

};

/*
void NavalBattle::Run()
{
	std::pair<int, int> m_Coordinates;
	std::cout << "\n Informe as COORDENADAS para atacar: \n";
	std::cin >> m_Coordinates.first;
	std::cin >> m_Coordinates.second;


}
*/

const void NavalBattle::Menu() 
{
	int op;
	std::string nickName;

	std::cout << "\n ----- [ MENU ]\n\n";
	std::cout << R"( 1 - Entrar no Servidor
 2 - Cadastra Navios
 3 - Imprimir o Tabuleiro
 0 - Sair )" << '\n';
	std::cout << "\n-----> Informe a opção: ";
	std::cin >> op;
	std::cin.clear();

	switch (op)
	{
	case 1:
		std::cin.ignore();
		m_Client = new Client;
		m_Client->StartClient();
		//Menu();
		break;
	case 2:
		std::cout << "\n Informe a opção: ";
	case 3:
		std::cout << "\n Informe a opção: ";
	default:
		break;
	}



}



