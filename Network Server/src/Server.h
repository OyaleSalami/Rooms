#define DEFAULT_PORT "27015"
#define DEFAULT_BUFFER_LENGTH 512

#pragma once
#include "Debug.h"
#include <vector>

#include <Winsock2.h>
#include <Ws2tcpip.h>

namespace Network
{
	class Server
	{
	public:
		int port; 
		int maxPlayers;
		bool isRunning = false;
		SOCKET ListenSocket = INVALID_SOCKET;
		std::vector<SOCKET> clients;
		
		void Start(const int& _maxPlayers)
		{
			maxPlayers = _maxPlayers;
			isRunning = true;
			prefill();

			Configure();
			Bind();
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
				WSACleanup();
				return 1;
			}

			ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
			if (ListenSocket == INVALID_SOCKET)
			{
				Debug::Error("Error at socket(): " + WSAGetLastError());
				freeaddrinfo(result);
				WSACleanup();
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
				freeaddrinfo(result);
				closesocket(ListenSocket);
				WSACleanup();
				return 1;
			}

			freeaddrinfo(result);
			return 0;
		}

		void Update()
		{
			await();
		}

		void prefill()
		{
			for (int i = 1; i <= maxPlayers; i++)
			{
				clients.push_back(SOCKET(INVALID_SOCKET));
			}
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
			for (int i = 1; i <= maxPlayers; i++)
			{
				if (clients[i] == INVALID_SOCKET)
				{
					//Accept a client socket
					clients[i] = accept(ListenSocket, NULL, NULL);

					if (clients[i] == INVALID_SOCKET)
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

			closesocket(ListenSocket);
			WSACleanup();
		}

		~Server()
		{
			freeaddrinfo(result);
			close();
		}


	private:
		int iResult;
		struct addrinfo* result = NULL, * ptr = NULL, hints;

	};
}