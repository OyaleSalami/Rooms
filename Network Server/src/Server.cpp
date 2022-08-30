#include "Server.h"

namespace Network
{
	Server::Server(const int &_maxPlayers, const int &_port)
	{
		maxPlayers = _maxPlayers;
		clients.resize(_maxPlayers); //Set the list to take (maxPlayers) no of players
		port = _port;
	}

	void Server::Start()
	{
		//Create socket
		if (ListenSocket.Create() == NetResult::Success)
		{
			Debug::Log("Socket created", false);
			running = true;
			listen = true;

			//Bind Socket
			if (ListenSocket.Bind(Endpoint("0.0.0.0", port)) != NetResult::Success)
			{
				Debug::Error("Failed to bind socket");
			}
		}
		else
		{
			Debug::Error("Failed to create socket");
		}
	}

	void Server::Update()
	{
		//Listen
		if (ListenSocket.Listen(Endpoint("0.0.0.0", port)) == NetResult::Success)
		{
			Debug::Log("Socket successfully listening on port: " + std::to_string(port), false);
			
			TcpSocket newConnection;
			
			int _id = GetNext();
			if (_id == -1)
			{
				Debug::Log("Max connections have been accepted", false);
				listen = false;
				return;
			}

			clients[_id].id = _id; //Set the id for the Client class

			//Accept
			if (ListenSocket.Accept(clients[_id].tcp) == NetResult::Success)
			{
				Debug::Log("New connection accepted", false);
			}
			else
			{
				Debug::Error("Failed to accept the new connection");
			}
		}
		else
		{
			Debug::Error("Failed to listen for new connections", false);
		}

		Message message(MessageType::Chat);
		message.Write(std::string("Hello, form the server"));

		SendToAll(SendMode::Tcp, message);
	}

	void Server::Stop()
	{
		running = false;
		listen = false;
		ListenSocket.Close();
	}

	int Server::GetNext()
	{
		for (int i = 0; i < maxPlayers; i++)
		{
			if (clients[i].GetId() == -1)
			{
				return i;
			}
		}

		return -1;
	}

	void Server::SendToAll(SendMode mode, const Message& message)
	{
		if (mode == SendMode::Tcp)
		{
			for (int i = 0; i < maxPlayers; i++)
			{
				if (clients[i].GetId() != -1)
				{
					clients[i].tcp.SendAll(message.buffer.data(), message.buffer.size());
				}
			}
		}
	}
}