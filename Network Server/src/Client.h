#pragma once

#include "Endpoint.h"
#include "Debug.h"
#include "TCP.h"
#include "UDP.h"

namespace Network
{
	class Client
	{
	public:
		int id = -1;
		Endpoint endpoint;
		TcpSocket tcp;
		bool isConnected = false;
		SOCKET udp = INVALID_SOCKET;

		int offset = 0;
		int msgSize = 0;
		char buffer[MAX_MSG_SIZE];

		/// <summary>Default constructor</summary>
		Client() {}

		/// <summary>A client to represent a remote host</summary>
		/// <param name="_tcp">TcpSocket of the remote host</param>
		Client(SOCKET &_tcp);

		/// <summary>A client to represent a remote host</summary>
		/// <param name="_tcp">TcpSocket of the remote host</param>
		/// <param name="_udp">UdpSocket of the remote host</param>
		Client(SOCKET &_tcp, SOCKET &_udp);

		Message Update(); //Receive data from the server
		void Disconnect(std::string note); //Disconnnect client from the server

		int GetId();
	};
}