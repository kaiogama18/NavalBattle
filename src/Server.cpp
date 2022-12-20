#include <iostream>
#include <thread>
#include <string>
#include <WinSock2.h>
#include <vector>

#pragma comment (lib, "ws2_32.lib")

SOCKET		Connections[100];			// Definição do número máximo de clientes
int			Counter = 0;				// Auxiliar para contar o número de clientes
fd_set		master;						// para colocar soquetes em um conjunto.

// Thread para tratar o Cliente //
void ConnectionHandler(int index)
{
	char nickname[50];
	ZeroMemory(nickname, 50);
	recv(Connections[index], nickname, sizeof(nickname), 0);
	
	std::string message = "-----> Bem vindo ao Servidor Batalha Naval ";
	message = message + nickname;

	send(Connections[index], message.c_str(), strlen(message.c_str()), 0);
	std::cout << "\n-----> Jogador(a) [" << index << "]: [ " << nickname << " ] entrou no Servidor!" << '\n';

	if (index > 0 && index < 2)
		std::cout << "----- Começou o jogo -----\n\n";
}

// Para varias chamadas de clientes usando threads //
void AcceptHandler(SOCKET connection)
{
	while (true)
	{
		SOCKET newConnection;
		for (int i = 0; i < 100; i++)
		{
			newConnection = ::accept(connection, nullptr, nullptr);

			if (newConnection == 0)
			{
				std::cout << "Error #2\n";
			}
			else if (newConnection == INVALID_SOCKET)
			{
				std::cout << "Error: " << WSAGetLastError() << '\n';
				closesocket(newConnection);
			}
			else
			{
				Connections[i] = newConnection;
				Counter++;
				std::thread connectionHandler = std::thread(ConnectionHandler, i);
				connectionHandler.detach();
				FD_SET(newConnection, &master);

			}
		}
	}
}


void SendHandler(SOCKET cliente)
{
	std::string data;
	do
	{
		std::cout << "Servidor: ";
		getline(std::cin, data);
		data = "Server: " + data;
		for (auto i = 0; i < master.fd_count; i++)
		{
			auto result = send(master.fd_array[i], data.c_str(), strlen(data.c_str()), 0);
			if (result == SOCKET_ERROR)
			{
				std::cout << '\r';
				std::cout << "send to client " << i << " failed: " << WSAGetLastError() << '\n';
				return;
			}
		}
	} while (data.size() > 0);
}

void StartServer()
{

	WSADATA version;

	// Função para inicialização para o windows
	if (WSAStartup(MAKEWORD(2, 2), &version) != 0)
	{
		std::cout << "WSADATA ERROR : Error no winsock. " << '\n';
		return;
	}
	std::cout << " WSAStartup OK!\n";

	SOCKET servidor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (servidor == INVALID_SOCKET)
	{
		std::cout << " Error: Falhou na criação do Socket ! \n";
		return;
	}
	std::cout << " Socket criado com sucesso! \n";

	// Criação da estrutura do endereço //
	struct sockaddr_in servidorAddr;								// Estrura para qual conectar
	servidorAddr.sin_family = AF_INET;								// Ip versão 4
	servidorAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");		// Identifica o endereço do servidor em bit
	servidorAddr.sin_port = htons(1111);							// Qual a porta que o servidor vai usar 

	// Conexão com servidor //
	auto result = bind(servidor, (sockaddr*)&servidorAddr, sizeof(servidorAddr));
	if (result == SOCKET_ERROR)
	{
		std::cout << " Error: Listen falhou \n";
		closesocket(servidor);
		WSACleanup();
		return;
	}

	// listen : Permite ficar ouvindo se alguem solicitar conexão
	result = listen(servidor, SOMAXCONN);
	if (result == SOCKET_ERROR)
	{
		std::cout << " Error: Listen falhou \n";
		closesocket(servidor);
		WSACleanup();
		return;
	}
	std::cout << " Esperando Jogador! \n";

	// Thread para aceitar cliente
	std::thread acceptThread = std::thread(AcceptHandler, servidor);
	acceptThread.join();
	closesocket(servidor);
	WSACleanup();
}

int main()
{
	setlocale(LC_ALL, "portuguese");
	setlocale(LC_ALL, "en_US");
	std::cout << "----- Servidor: Batalha Naval -----\n\n";
	StartServer();
	system("PAUSE");
	return 0;
}