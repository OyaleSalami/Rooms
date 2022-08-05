#define DEFAULT_PORT "27015"
#define DEFAULT_BUFF_LENGTH 512

#pragma once
#include <vector>
#include "Debug.h"
#include "Endpoint.h"

#include <Winsock2.h>
#include <Ws2tcpip.h>

namespace Network
{
	class Client
	{
	public:
		int id;
		Endpoint endpoint;  // The client's endpoint information
	};

	class Lobby
	{
	public:
		int maxPlayers;
		std::vector<SOCKET> clients;

		Lobby() {}
		Lobby(const int &max)
		{
			maxPlayers = max;
		}
		void load()
		{
			for (int i = 0; i < maxPlayers; i++)
			{
				clients.push_back(SOCKET(INVALID_SOCKET));
			}
		}

		bool isFull()
		{
			for (int i = 0; i < maxPlayers; i++)
			{
				if (clients[i] == INVALID_SOCKET) { return false; }
			}

			return true;
		}
	};

	class Server
	{
	public:
		int port;
		bool isRunning = false;

		Lobby lobby;
		char recvbuf[DEFAULT_BUFF_LENGTH];
		SOCKET ListenSocket = INVALID_SOCKET;
		
		Server();
		Server(const int& maxPlayers)
		{
			lobby = Lobby(maxPlayers);
			lobby.load();
		}

		void Start()
		{
			isRunning = true;
			Configure();
			Bind();
		}

		void Update()
		{
			char text[] = "Default text something";
			if (lobby.isFull() != true) 
			{ 
				await();
			}

			for (int i = 0; i < lobby.maxPlayers; i++)
			{
				if (lobby.clients[i] != INVALID_SOCKET)
				{
					Send(lobby.clients[i], text, sizeof(text), 0);
				}
			}
		}

		int Configure()
		{
			ZeroMemory(&hints, sizeof(hints));
			hints.ai_family = AF_INET;
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_protocol = IPPROTO_TCP;
			hints.ai_flags = AI_PASSIVE;

			//Resolve the local address and port to be used by the server
			iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
			if (iResult != 0)
			{
				Debug::Error("Getaddrinfo failed: " + iResult);
				close();
				return 1;
			}

			ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
			if (ListenSocket == INVALID_SOCKET)
			{
				Debug::Error("Error at socket(): " + WSAGetLastError());
				close();
				return 1;
			}
			return 0;
		}

		int Bind()
		{
			// Setup the TCP listening socket
			iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
			if (iResult == SOCKET_ERROR) 
			{
				Debug::Error("Server Bind failed with error: " + WSAGetLastError());
				close();
				return 1;
			}
			return 0;
		}

		int Send(SOCKET &clientSocket, char* data, const int &length, const int &flags = 0)
		{
			int iSendResult;
			iSendResult = send(clientSocket, data, length, flags);

			if (iSendResult == SOCKET_ERROR) 
			{
				printf("send failed: %d\n", WSAGetLastError());
				close();
				return 1;
			}
			return 0;
		}

		int Receive(SOCKET &clientSocket, char* recvBuff, const int &buffLen = DEFAULT_BUFF_LENGTH, const int &flags = 0)
		{
			iResult = recv(clientSocket, recvBuff, buffLen, flags);
			if (iResult > 0)
			{
				printf("Bytes received: %d\n", iResult);
			}

			return 0;
		}
		
		int await()
		{
			if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) //Listen for a connection
			{
				Debug::Error("Listen failed with error: " + WSAGetLastError());
				close();
				return 1;
			}

			//Accept the connection

			for (int i = 0; i < lobby.maxPlayers; i++)
			{
				

				if (lobby.clients[i] == INVALID_SOCKET)
				{
					//Accept a client socket
					lobby.clients[i] = accept(ListenSocket, NULL, NULL);

					if (lobby.clients[i] == INVALID_SOCKET)
					{
						Debug::Error("Accept failed: " + WSAGetLastError());
						close();
						return 1;
					}
					Debug::Log("Client connection accepted");
					break;
				}
			}
			
			return 0;
		}

		void close()
		{
			isRunning = false;
			freeaddrinfo(result);
			closesocket(ListenSocket);
			WSACleanup();
		}

		~Server()
		{
			close();
		}

	private:
		int iResult;
		struct addrinfo* result = NULL, * ptr = NULL, hints;

	};
}