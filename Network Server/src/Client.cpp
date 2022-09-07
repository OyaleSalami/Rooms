#include "Client.h"

namespace Network
{
	void Client::Connect(int _id, SOCKET& _tcp)
	{
		id = _id;
		tcp = TcpSocket(_tcp);
	}

	void Client::Connect(int _id, SOCKET& _tcp, SOCKET& _udp)
	{
		id = _id;
		tcp = TcpSocket(_tcp);
		udp = _udp;
	}

	void Client::Disconnect()
	{
		tcp.Close();
		closesocket(udp);
	}

	void Client::Update()
	{
		if (tcp.handle != INVALID_SOCKET)
		{
		}
		else
		{
			Debug::Error("Invalid Client Socket: " + std::to_string(id));
		}
	}

	int Client::GetId()
	{
		return id;
	}
}