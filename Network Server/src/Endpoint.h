#pragma once
#include <string>

namespace Network
{
	class Endpoint
	{
	public:
		int port;
		std::string address;

		void Reset()
		{
			port = NULL;
			address.clear();
		}
	};
}