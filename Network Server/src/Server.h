#pragma once

#include <vector>
#include "TCP.h"
#include "Client.h"

namespace Network
{
	class Server
	{
	public:
		bool running; ///Represents the server's state
		bool listening; ///Is the server listening for new connections or not
		TcpSocket ListenSocket; ///Listen Socket for TCP Connections
		std::vector<Client> clients; ///List of connected clients

		/// <summary>Default constructor: Sets max player and port</summary>
		Server(const int& maxPlayers, const int &_port, const std::string& address);
		/// <summary>Creates and Binds the socket</summary>
		void Start();
		/// <summary>Logic for server(Listen, Accept, Send, Receive)</summary>
		void Update();
		/// <summary>Stops listening and closes the service</summary>
		void Stop();
		/// <summary>Sends the message to all connected clients over a particular transport</summary>
		void SendToAll(SendMode mode, const Message &message);
		/// <summary>Disconnects a client from the server</summary>
		void DisconnectClient(int id, std::string note);

	private:
		std::vector<WSAPOLLFD> clientFd;
		int maxPlayers; ///Max accepted players on the server
		Endpoint endpoint; ///Endpoint of the server
	};
}