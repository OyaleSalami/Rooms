#pragma once
#include "Endpoint.h"
#include "TCP.h"
#include "UDP.h"

namespace Network
{
	class Player
	{
	public: 
		int id;
		sockaddr addr;
		int tcpClient;

		Player(const int& _id)
		{
			id = _id;
		}

		void Disconnect()
		{
			tcpClient = NULL;
		}
	};
}