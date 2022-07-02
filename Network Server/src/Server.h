#pragma once
#include "TcpListener.h"
#include <string>

namespace Network
{
	class Server
	{
	public:
		int port; 
		bool isRunning;

		TcpListener listener;
		
		void Start(const int &_port)
		{
			port = _port;

			//Starts listening for connections
			listener.Start();
			isRunning = true;
		}

		void Update()
		{
			listener.Update();
		}
	};
}