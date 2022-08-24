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
		void Start(); //Starts the server
		void Update(); //Starts listening and accepting clients
		void Stop();

		int GetNext();

		void SendToAll(SendMode mode, const Message &message);
	private:
		int maxPlayers = 0;
		bool listen = false;
	};
}