#pragma once
#include "Endpoint.h"

namespace Network
{
	///<summary>A player abstraction class on the server</summary>
	class Player
	{
	public:
		
	};

	class Client
	{
	public:
		int id;
		Player player;		// One player per client
		Endpoint endpoint;  // The client's endpoint information
	};

}