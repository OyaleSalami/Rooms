#pragma once

#include "TCP.h"
#include "Client.h"
#include <vector>

namespace Network
{
	class Server
	{
	public:
		bool running = false;
		TcpSocket ListenSocket;
		std::vector<Client> clients;

		Server(const int& maxPlayers);
		void Start();
		void Update();
		void Stop();
	};
}