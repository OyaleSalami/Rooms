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
		clients.clear();
		clientFd.clear();

		//Create the listen socket
		if (ListenSocket.Create() == NetResult::Success)
		{
			running = true;
			listening = true;
			
			//Set it as a non-blocking socket
			ListenSocket.Set(true);

			//Bind the socket to an endpoint
			ListenSocket.Bind(endpoint);

			//Start listening for new connections
			ListenSocket.Listen(endpoint);

			WSAPOLLFD listenSocketFd = {};
			listenSocketFd.fd = ListenSocket.handle;
			listenSocketFd.events = POLLRDNORM;
			listenSocketFd.revents = 0;

			clientFd.push_back(listenSocketFd);

			Debug::Log("Socket is listeneing ...");
		}
		else
		{
			Debug::Error("Failed to create socket");
		}
	}

	void Server::Update()
	{
		if (WSAPoll(clientFd.data(), clientFd.size(), 1) > 0)
		{
			//The listen socket is the first item on the array 
			WSAPOLLFD& listenSocket = clientFd[0];

			if (listenSocket.revents & POLLRDNORM)
			{
				TcpSocket connection;
				//Accept the new connections
				if (ListenSocket.Accept(connection) == NetResult::Success)
				{
					clients.emplace_back(connection.handle);
					Debug::Log("New connection accepted");

					WSAPOLLFD connectionFd = {};
					connectionFd.fd = connection.handle;
					connectionFd.events = POLLRDNORM;
					connectionFd.revents = 0;

					clientFd.push_back(connectionFd);
				}
				else
				{
					Debug::Error("No new connection accepted");
				}
			}

			for (int i = clientFd.size()-1; i >= 1; i--)
			{
				int id = i - 1;
				Client current = clients[id];

				//Error handling
				if (clientFd[i].revents & (POLLERR || POLLHUP || POLLNVAL)) //Error occured
				{
					DisconnectClient(id, "Polling Error");
					continue; //Skip to the next one and dont bother handling data
				}

				//Handling data
				if (clientFd[i].revents & POLLRDNORM)
				{
					current.Update(); //Update the client(Receive data)
				}
			}
		}
	}

	void Server::Stop()
	{
		running = false;
		listening = false;
		endpoint.Reset();
		ListenSocket.Close();
	}

	void Server::SendToAll(SendMode mode, const Message& message)
	{
		//TODO: Only TCP Implemented for now
		if (mode == SendMode::Tcp)
		{
			for (unsigned int i = 0; i < clients.size(); i++)
			{
				if (clients[i].tcp.handle != INVALID_SOCKET)
				{
					clients[i].tcp.SendAll(message.buffer.data(), message.buffer.size());
				}
			}
		}
	}

	void Server::DisconnectClient(int id, std::string note)
	{
		clientFd.erase(clientFd.begin() + id + 1);
		
		clients[id].Disconnect(note);
		clients.erase(clients.begin() + id);

		Debug::Warning("Connection lost: " + note);
	}
}