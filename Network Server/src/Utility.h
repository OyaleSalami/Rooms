#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Winsock2.h>
#include <Ws2tcpip.h>
#include "Debug.h"

namespace Network
{
	namespace Util
	{
		enum class IPVersion
		{
			Invalid,
			IPv4
		};

		enum class NetResult
		{
			Success,
			Error
		};
	}

	class NetworkSystem
	{
	public:
		static bool Initialize()
		{
			WSADATA wsadata;
			int result = WSAStartup(MAKEWORD(2, 2), &wsadata);

			if (result != 0)
			{
				throw NetworkException("Failed to startup the winsock API");
				return false;
			}

			if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wVersion) != 2)
			{
				throw new NetworkException("Could not find a usable version of the winsock API dll");
				return false;
			}

			return true;
		}

		static void ShutDown()
		{
			WSACleanup();
		}
	};
}