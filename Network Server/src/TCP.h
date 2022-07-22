#pragma once
#define DEFAULT_BUFFER_LENGTH 512

#include <stdio.h>
#include <iostream>

#ifdef LINUX
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
#endif // LINUX

#pragma comment (lib, "ws2_32.lib")
#include <Winsock2.h>
#include <Ws2tcpip.h>

namespace Network
{
	///<summary>Class abstraction for a TCP-Client Socket</summary>
	class TCPClient
	{
	public:
		SOCKET socket;
		bool isConnected;

		/// <summary>Connects the TCP Client to a socket bound to a remote host</summary>
		/// <param name="_acceptSocket">The socket bound to the remote host</param>
		void Connect(SOCKET &_acceptSocket)
		{
			socket = _acceptSocket;
			isConnected = true;
		}

		/// <summary>Send data to the bound remote host</summary>
		/// <param name="sendBuffer">The byte array to be sent</param>
		/// <param name="offset">Offset to where the data should be read from</param>
		/// <param name="length">Length of the dat to be sent</param>
		/// <param name="flags">Flags anyone??</param>
		void Write(const char* sendBuffer, int offset, int length, int flags = 0)
		{
			int result;
			if (socket != INVALID_SOCKET)
			{
				result = send(socket, sendBuffer, length, flags);

				if (result == SOCKET_ERROR)
				{
					//TODO: throw exception here
				}
			}
			else
			{
				//TODO: Throw an error for invalid sockets
			}
		}

		/// <summary>Receive data from the remote host</summary>
		/// <param name="recvBuffer">The buffer to store the received data</param>
		/// <param name="offset">Offset to where the data should be read from</param>
		/// <param name="length">Length of the data to be read default = DEFAULT_BUFFER_LENGTH</param>
		/// <param name="flags">Flags anyone??</param>
		void Read(char* recvBuffer, int offset, int length, int flags = 0)
		{
			int result;
			if (socket != INVALID_SOCKET)
			{
				result = recv(socket, recvBuffer, length, flags);

				if (result == SOCKET_ERROR)
				{
					//TODO: throw exception here
				}
			}
			else
			{
				//TODO: Throw an error for invalid sockets
			}
		}

		/// <summary>Disconnect the socket from the remote host (Unbind it)</summary>
		void Disconnect()
		{
			isConnected = false;
			closesocket(socket);
			shutdown(socket, SD_SEND);
		} 

	private:
		~TCPClient()
		{
			WSACleanup();
		}
	};

	class TcpListener
	{
	public:
		int port;

		void Init()
		{
			//Initialize Winsock
			int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

			hints.ai_family = AF_INET;
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_protocol = IPPROTO_TCP;
			hints.ai_flags = AI_PASSIVE;

			if (iResult != 0)
			{
			}
		}

	private:
		WSADATA wsaData;
		struct addrinfo hints;
		struct addrinfo* ptr = NULL;
		struct addrinfo* result = NULL;

		void CleanUp()
		{
			WSACleanup();
		}
	};

}