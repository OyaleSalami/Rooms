#include "Endpoint.h"

namespace Network
{
	Endpoint::Endpoint(const char* ip, unsigned short port)
	{
		this->port = port;

		//IPv4
		in_addr addr; //IPV4 address
		//Presentation format to network format
		int result = inet_pton(AF_INET, ip, &addr);

		if (result == 1)
		{
			if (addr.S_un.S_addr != INADDR_NONE)
			{
				address = ip;
				hostname = ip;

				ip_bytes.resize(sizeof(ULONG));
				memcpy(&ip_bytes[0], &addr.S_un.S_addr, sizeof(ULONG));

				ipversion = IPVersion::IPv4;
				return;
			}
		}

		//Attempt to resolve hostname to IPV4 address
		addrinfo hints = {};
		hints.ai_family = AF_INET; //IPV4 addresses only

		addrinfo* hostinfo = nullptr;
		result = getaddrinfo(ip, NULL, &hints, &hostinfo);

		if (result == 0)
		{
			sockaddr_in* host_addr = reinterpret_cast<sockaddr_in*>(hostinfo->ai_addr);

			host_addr->sin_addr.S_un.S_addr;
			address.resize(16);
			inet_ntop(AF_INET, &host_addr->sin_addr, &address[0], 16);

			hostname = ip;

			ULONG ip_long = host_addr->sin_addr.S_un.S_addr;
			ip_bytes.resize(sizeof(ULONG));
			memcpy(&ip_bytes[0], &ip_long, sizeof(ULONG));
			ipversion = IPVersion::IPv4;

			freeaddrinfo(hostinfo);
			return;
		}
	}

	Endpoint::Endpoint(sockaddr* addr)
	{
		if (addr->sa_family == AF_INET)
		{
			sockaddr_in* addrv4 = reinterpret_cast<sockaddr_in*>(addr);
			ipversion = IPVersion::IPv4;
			port = ntohs(addrv4->sin_port);
			ip_bytes.resize(sizeof(ULONG));
			memcpy(&ip_bytes[0], &addrv4->sin_addr, sizeof(ULONG));

			address.resize(16);
			inet_ntop(AF_INET, &addrv4->sin_addr, &address[0], 16);
			hostname = address;
		}
	}

	IPVersion Endpoint::GetIPVersion()
	{
		return ipversion;
	}

	std::vector<uint8_t> Endpoint::GetIPBytes()
	{
		return ip_bytes;
	}

	std::string Endpoint::GetHostName()
	{
		return hostname;
	}

	std::string Endpoint::GetIpString()
	{
		return address;
	}

	unsigned short Endpoint::GetPort()
	{
		return port;
	}

	sockaddr_in Endpoint::GetSockaddrIPv4()
	{
		sockaddr_in addr = {};
		addr.sin_family = AF_INET;
		memcpy(&addr.sin_addr, &ip_bytes[0], sizeof(ULONG));
		addr.sin_port = htons(port);

		return addr;
	}

	void Endpoint::Reset()
	{
		port = 0;
		address.clear();
		hostname.clear();
		ip_bytes.clear();
		ipversion = IPVersion::Invalid;
	}
}