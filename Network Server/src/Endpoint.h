#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Winsock2.h>
#include <Ws2tcpip.h>

#include <string>
#include <vector>
#include "Utility.h"

using namespace Network::Util;

namespace Network
{
	///<summary> A class to hold information about a remote host</summary>
	class Endpoint
	{
	public:
		Endpoint() {}
		Endpoint(const char* address, unsigned short port);
		Endpoint(sockaddr* addr);
		IPVersion GetIPVersion();
		std::vector<uint8_t> GetIPBytes();
		std::string GetHostName();
		std::string GetIpString();
		unsigned short GetPort();
		sockaddr_in GetSockaddrIPv4();
		sockaddr_in6 GetSockaddrIPv6();
		void Print();

	private:
		unsigned short port = 0; //Port of the remote host
		std::string address; //Address of the remote host
		std::string hostname = ""; //Hostname of the Remote host
		std::vector<uint8_t> ip_bytes; //IP address represented in bytes
		IPVersion ipversion = IPVersion::Invalid; //IPVersion of the endpoint
	};
}