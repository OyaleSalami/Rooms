#pragma once
#include <string>

namespace Network
{
	/// <summary>
	/// A class to hold information about a remote host
	/// </summary>
	class Endpoint
	{
	public:
		int port; //Port of the remote host
		std::string address; //Address of the remote host

		Endpoint() {}

		Endpoint(const int &_port, const std::string &_address)
		{
			port = _port;
			address = _address;
		}

		/// <summary>Reset the class so it doesn't point to any remote host</summary>
		void Reset()
		{
			port = 0;
			address.clear();
		}
	};
}