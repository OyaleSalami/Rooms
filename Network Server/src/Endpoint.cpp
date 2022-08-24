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

		//Attempt to resolve hostnam to IPV4 address
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

		//IPv6
		in6_addr addr6; //IPV6 address
		//Presentation format to network format
		result = inet_pton(AF_INET6, ip, &addr6);

		if (result == 1)
		{
			address = ip;
			hostname = ip;

			ip_bytes.resize(16);
			memcpy(&ip_bytes[0], &addr6.u, 16);

			ipversion = IPVersion::IPv6;
			return;
		}

		//Attempt to resolve hostnam to IPV6 address
		addrinfo hintsv6 = {};
		hints.ai_family = AF_INET6; //IPV6 addresses only

		addrinfo* hostinfov6 = nullptr;
		result = getaddrinfo(ip, NULL, &hintsv6, &hostinfov6);
		if (result == 0)
		{
			sockaddr_in6* host_addr = reinterpret_cast<sockaddr_in6*>(hostinfov6->ai_addr);

			address.resize(46);
			inet_ntop(AF_INET6, &host_addr->sin6_addr, &address[0], 46);

			hostname = ip;

			ip_bytes.resize(16);
			memcpy(&ip_bytes[0], &host_addr->sin6_addr, 16);
			ipversion = IPVersion::IPv6;

			freeaddrinfo(hostinfov6);
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
		else //IPv6
		{
			sockaddr_in6* addrv6 = reinterpret_cast<sockaddr_in6*>(addr);
			ipversion = IPVersion::IPv6;
			port = ntohs(addrv6->sin6_port);
			ip_bytes.resize(16);
			memcpy(&ip_bytes[0], &addrv6->sin6_addr, 16);

			address.resize(46);
			inet_ntop(AF_INET6, &addrv6->sin6_addr, &address[0], 46);
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
		if (ipversion != IPVersion::IPv4)
		{
			throw NetworkException("IP Adress is not IPv4");
		}

		sockaddr_in addr = {};
		addr.sin_family = AF_INET;
		memcpy(&addr.sin_addr, &ip_bytes[0], sizeof(ULONG));
		addr.sin_port = htons(port);

		return addr;
	}

	sockaddr_in6 Endpoint::GetSockaddrIPv6()
	{
		if (ipversion != IPVersion::IPv6)
		{
			throw NetworkException("IP Adress is not IPv4");
		}

		sockaddr_in6 addr = {};
		addr.sin6_family = AF_INET6;
		memcpy(&addr.sin6_addr, &ip_bytes[0], 16);
		addr.sin6_port = htons(port);

		return addr;
	}

	void Endpoint::Print()
	{
		switch (ipversion)
		{
		case IPVersion::IPv4:
			Debug::Log("IP version: IPv4", false);
			break;

		case IPVersion::IPv6:
			Debug::Log("IP version: IPv6", false);
			break;

		default:
			Debug::Log("Invalid IP version", false);
		}

		Debug::Log("Hostname: " + hostname, false);
		Debug::Log("IP: " + address, false);
		Debug::Log("Port: " + port, false);
		Debug::Log("IP bytes: ", false);

		for (auto& digit : ip_bytes)
		{
			std::string a = "" + (int)digit;
			Debug::Log(a, false);
		}
	}
}