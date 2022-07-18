#pragma once

#pragma comment (lib, "ws2_32.lib")
#include <Winsock2.h>

namespace Network
{
	class TcpListener
	{
	public:
		int socketfd, port;
		sockaddr_in server_addr;

		void init()
		{
			socketfd = socket(AF_INET, SOCK_STREAM, 0);

			if (socketfd < 0)
			{
				Debug().Error("Socket not opened!");
			}

			server_addr.sin_family = AF_INET;
			server_addr.sin_addr.s_addr = INADDR_ANY;
			server_addr.sin_port = htons(port);

			if (bind(socketfd, (sockaddr*)&server_addr, sizeof(server_addr)))
			{
				Debug().Error("Socket not bound!");
			}
		}

		/// <summary> Starts Listening and acceptipng connections </summary>
		void Start()
		{
			listen(socketfd, 10);
		}

		void Stop()
		{

		}
		
		void Update()
		{

		}

	};
}
