#include "Client.h"

namespace Network
{
	Client::Client(SOCKET& _tcp)
	{
		tcp = TcpSocket(_tcp);
		isConnected = true;

		//Set the socket to non-blocking
		tcp.Set(true);
	}

	Client::Client(SOCKET& _tcp, SOCKET& _udp)
	{
		tcp = TcpSocket(_tcp);
		udp = _udp;
	}

	void Client::Disconnect(std::string note)
	{
		Debug::Error("Disconnected: " + note);
		tcp.Close();
		closesocket(udp);
	}

	Message Client::Update()
	{
		//Reset the buffer

		//Handling data
		int recvdBytes = 0;

		recvdBytes = recv(tcp.handle, buffer, MAX_MSG_SIZE, 0);

		if (recvdBytes == 0) //Lost connection
		{
			Disconnect("Connection Lost: RECV == 0");
		}
		if (recvdBytes == SOCKET_ERROR) //Lost connection
		{
			int error = WSAGetLastError();
			if (error != WSAEWOULDBLOCK)
			{
				Disconnect("RECV < 0");
			}
		}
		if (recvdBytes > 0) //Succesfully read something
		{
			Message msg = Message((char*)buffer, recvdBytes);
			int size;
			msg.Read(size, false);

			if (recvdBytes < size)
			{
				Debug::Log("Received buffer size is: " + std::to_string(recvdBytes));
				Debug::Log("Message size is: " + std::to_string(size));

				Debug::Log("Message is still left to be read");
			}

			msg.Read(size); //Read out the size of the message

			//Handle data
			if (msg.Handle() == false)
			{
				Debug::Error("Unable to handle messsage!");
			}

			return msg;
		}
	}

	int Client::GetId()
	{
		return id;
	}

}