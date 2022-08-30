#include "Server.h"

namespace Network
{
	Server::Server(const int &_maxPlayers)
	{
		maxPlayers = _maxPlayers;
		clients.resize(_maxPlayers);
	}

	void Server::Start()
	{
		if (ListenSocket.Create() == NetResult::Success)
		{
			Debug::Log("Socket created", false);
			running = true;
			listen = true;
		}
		else
		{
			Debug::Error("Failed to create socket");
		}
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

	void Server::Update()
	{
		if (listen == false) { return; }

		//Listen
		if (ListenSocket.Listen(Endpoint("0.0.0.0", 8088)) == NetResult::Success)
		{
			Debug::Log("Socket successfully listening", false);
			TcpSocket newConnection;
			
			int id = GetNext();
			if (id == -1)
			{
				Debug::Log("Max connections accepted", false);
				listen = false;
				return;
			}
			clients[id].id = id;

			//Accept
			if (ListenSocket.Accept(clients[id].tcp) == NetResult::Success)
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
	}

	void Server::Stop()
	{
		running = false;
		listen = false;
		ListenSocket.Close();
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