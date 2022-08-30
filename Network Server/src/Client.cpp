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

	int Client::GetId()
	{
		return id;
	}
}