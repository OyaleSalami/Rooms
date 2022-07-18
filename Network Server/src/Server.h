#pragma once
#include "TcpListener.h"
#include <string>

namespace Network
{
	class Server
	{
	public:
		int port; 
		bool isRunning = false;

		TcpListener listener;
		
		void Start(const int &_port)
		{
			Debug().Log("Server started");
			port = _port;

			listener.init();
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