#pragma once

#include "TCP.h"
#include "Client.h"
#include <vector>

namespace Network
{
	class Server
	{
	public:
		bool running; //Represents the server's state
		TcpSocket ListenSocket; //Listen Socket for TCP Connections
		std::vector<Client> clients; //List of connected clients

		/// <summary>Default constructor: Sets max player and port</summary>
		Server(const int& maxPlayers, const int &_port);
		/// <summary>Creates and Binds the socket</summary>
		void Start();
		/// <summary>Logic for server(Listen, Accept, Send, Receive)</summary>
		void Update();
		/// <summary>Checks for errors that occurred during listening</summary>
		NetResult CheckForErrors();
		void ListenAndAccept(int backlog);
		/// <summary>Stops listening and closes the service</summary>
		void Stop();

		int GetNext();
		void SendToAll(SendMode mode, const Message &message);

	private:
		int port; //Port the server listens on
		int maxPlayers; //Max accepted players on the server
		bool listening; //Is the server listening for new connections or not
		Endpoint endpoint;

		std::vector<std::future<int>> Errors;
	};
}