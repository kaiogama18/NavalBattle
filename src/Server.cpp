#include <iostream>
#include <thread>
#include <string>
#include <WinSock2.h>
#include <vector>
#include <mutex>
#include <condition_variable>
#pragma comment (lib, "ws2_32.lib")

fd_set master; // para colocar soquetes em um conjunto.
 
// Thread para tratar o Cliente
void ConnectionHandler(SOCKET cliente)
{
	char nickname[50];
	ZeroMemory(nickname, 50);
	recv(cliente, nickname, sizeof(nickname), 0);

	std::string message = "-----> Bem vindo ao Servidor Batalha Naval ";
	message = message + nickname;
	for (auto i = 0; i < master.fd_count; i++)
	{
		send(master.fd_array[i], message.c_str(), strlen(message.c_str()), 0);
	}

	std::cout << "\n-----> Jogador(a) [" << master.fd_count << "]: [ " << nickname << " ] entrou no Servidor!" << '\n';
}

// Para varias chamadas de clientes usando threads
void AcceptHandler(SOCKET connection)
{
	while (true)
	{
		// SOCKET client -> Pegando o endereço da estrutura
		auto cliente = ::accept(connection, nullptr, nullptr);
		if (cliente == INVALID_SOCKET)
		{
			std::cout << "Error: " << WSAGetLastError() << '\n';
			closesocket(cliente);
		}
		else
		{
			// Chamando a thread ConnectionHandler -> Ler a tratar o Cliente 
			std::thread connectionHandler = std::thread(ConnectionHandler, cliente);
			connectionHandler.detach();
			FD_SET(cliente, &master); // para colocar soquetes em um conjunto.t 
		}
	}
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

	auto servidor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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