#pragma once

class Client
{
public:
	Client();

	void	OutputData(std::string message);
	void	CleanUp(SOCKET soc);
	void* send_handle(SOCKET soc);
	void* recv_handle(SOCKET soc);

	std::string g_name;
};