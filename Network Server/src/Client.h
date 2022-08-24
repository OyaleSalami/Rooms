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
		/// The client's network identifier
		int id;
		/// The client's endpoint information
		Endpoint endpoint;
		///The client's tcp socket
		SOCKET tcp;
		///The client's udp socket
		SOCKET udp;
	};
}