#include "Server.h"

namespace Network
{
	Server::Server(const int& _maxPlayers, const int& _port, const std::string& address)
	{
		maxPlayers = _maxPlayers;
		clients.resize(_maxPlayers); //Set the list to take (maxPlayers) no of players
		endpoint = Endpoint(address.c_str(), _port); //Set the endpoint of the server
		listening = false;
		running = false;
	}

	void Server::Start()
	{
		//Create socket
		if (ListenSocket.Create() == NetResult::Success)
		{
			Debug::Log("Socket created", false);
			running = true;
			listening = true;

			//Bind Socket
			if (ListenSocket.Bind(endpoint) != NetResult::Success)
			{
				Debug::Error("Failed to bind socket");
			}
		}
		else
		{
			Debug::Error("Failed to create socket");
		}

		//Listen asynchronuously
		std::future<int> result = std::async(std::launch::async, listen, ListenSocket.handle, 100);
	}

	void Server::Update()
	{
		//Listen
		if (ListenSocket.Listen(endpoint) == NetResult::Success)
		{
			Debug::Log("Socket successfully listening on port: " + std::to_string(endpoint.GetPort()), false);
			
			TcpSocket newConnection;
			int _id = GetNext(); //Get the next free client space
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
	}

	void Server::Stop()
	{
		running = false;
		listening = false;
		endpoint.Reset();
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