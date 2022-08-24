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
		SOCKET udp = INVALID_SOCKET;

		Client(){}

		void Connect(int _id, SOCKET &_tcp);
		void Connect(int _id, SOCKET &_tcp, SOCKET &_udp);

		void Disconnect();

		int GetId();
	};
}