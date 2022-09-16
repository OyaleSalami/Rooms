#include "TCP.h"

namespace Network
{
	TcpSocket::TcpSocket(const SOCKET& _handle)
	{
		handle = _handle;
	}

	NetResult TcpSocket::Create()
	{
		if (handle != INVALID_SOCKET)
		{
			return NetResult::Error; //Trying to "create" an already created socket
		}

		//Attempt to create an IPv4 TCP socket
		handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (handle == INVALID_SOCKET)
		{
			//If socket creation failed
			int error = WSAGetLastError();
			Debug::Error("Error creating scoket: " + error);

			return NetResult::Error;
		}

		//TODO: Disable Nagles algorithm for TCP Sockets
		return NetResult::Success;
	}

	NetResult TcpSocket::Close()
	{
		if (handle == INVALID_SOCKET)
		{
			//Socket is probably closed already
			return NetResult::Error;
		}

		int result = closesocket(handle);

		if (result != 0) 
		{
			//If an error occurred while trying to close the socket
			return NetResult::Error;
		}

		handle = INVALID_SOCKET;
		return NetResult::Success;
	}

	NetResult TcpSocket::Bind(Endpoint endpoint)
	{
		sockaddr_in addr = endpoint.GetSockaddrIPv4();
		int result = bind(handle, (sockaddr*)&addr, sizeof(sockaddr_in));

		if (result != 0)
		{
			//Error while trying to bind a socket
			int error = WSAGetLastError();
			Debug::Error("Error while binding: " + error);

			return NetResult::Error;
		}

		return NetResult::Success;
	}

	NetResult TcpSocket::Listen(Endpoint endpoint, int backlog)
	{
		int result = listen(handle, backlog);

		if (result != 0)
		{
			int error = WSAGetLastError();
			Debug::Error("Error while listening: " + std::to_string(error));

			return NetResult::Error;
		}

		return NetResult::Success;
	}

	NetResult TcpSocket::Accept(TcpSocket& outSocket)
	{
		sockaddr_in addr = {};
		int len = sizeof(sockaddr_in);

		SOCKET newConnectionHandle = accept(handle, (sockaddr*)&addr, &len);

		if (newConnectionHandle == INVALID_SOCKET)
		{
			int error = WSAGetLastError();

			Debug::Error("Failed to accept the new connection: " + std::to_string(error));
			return NetResult::Error;
		}

		Endpoint newConnectionEndpoint((sockaddr*)&addr);
		outSocket = TcpSocket(newConnectionHandle);

		return NetResult::Success;
	}

	NetResult TcpSocket::Connect(Endpoint endpoint)
	{
		sockaddr_in addr = endpoint.GetSockaddrIPv4();
		int result = connect(handle, (sockaddr*)&addr, sizeof(sockaddr_in));

		if (result != 0)
		{
			int error = WSAGetLastError();
			return NetResult::Error;
		}

		return NetResult::Success;
	}

	NetResult TcpSocket::Send(const void* data, int numberOfBytes, int& bytesSent)
	{
		if (handle == INVALID_SOCKET)
		{
			Debug::Error("Invalid socket");
		}
		//Send data to (handle)
		bytesSent = send(handle, (const char*)data, numberOfBytes, NULL);

		if (bytesSent == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			Debug::Error("Error sending data: " + std::to_string(error));

			return NetResult::Error;
		}
		return NetResult::Success;
	}

	NetResult TcpSocket::Recv(void* destination, int numberOfBytes, int& bytesReceived)
	{
		bytesReceived = recv(handle, (char*)destination, numberOfBytes, NULL);
		
		//Connection closed gracefully
		if (bytesReceived == 0) 
		{
			Debug::Error("Connection closed gracefully while receiving data.");
			return NetResult::Error;
		}

		if (bytesReceived == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			Debug::Error("Error recieving data: " + std::to_string(error));

			return NetResult::Error;
		}

		return NetResult::Success;
	}

	NetResult TcpSocket::SendAll(const void* data, int numberOfBytes)
	{
		int totalBytesSent = 0;

		while (totalBytesSent < numberOfBytes)
		{
			int bytesRemaining = numberOfBytes - totalBytesSent;
			int bytesSent = 0;
			char* bufferOffset = (char*)data + totalBytesSent;

			NetResult result = Send(bufferOffset, bytesRemaining, bytesSent);
			if (result != NetResult::Success)
			{
				Debug::Error("Error sending data");
				return NetResult::Error;
			}
			totalBytesSent += bytesSent;
		}

		return NetResult::Success;
	}

	NetResult TcpSocket::RecvAll(void* destination, int numberOfBytes)
	{
		int totalBytesReceived = 0;

		while (totalBytesReceived < numberOfBytes)
		{
			int bytesRemaining = numberOfBytes - totalBytesReceived;
			int bytesReceived = 0;
			char* bufferOffset = (char*)destination + totalBytesReceived;

			NetResult result = Recv(bufferOffset, bytesRemaining, bytesReceived);
			if (result != NetResult::Success)
			{
				return NetResult::Error;
			}
			totalBytesReceived += bytesReceived;
		}

		return NetResult::Success;
	}

	NetResult TcpSocket::Send(Message& message)
	{
		NetResult result = SendAll(message.buffer.data(), message.buffer.size());

		if (result != NetResult::Success)
		{
			return NetResult::Error;
		}

		return NetResult::Success;
	}

	NetResult TcpSocket::Recv(Message& message)
	{
		int byteSize = 64;

		message.Clear();
		message.buffer.resize(byteSize);

		while (handle != INVALID_SOCKET)
		{
			//Try to recieve from  the remote client
			NetResult result = RecvAll(&message.buffer[0], byteSize);
			
			if (result != NetResult::Success)
			{
				Debug::Error("Error receiving data: ");
			}
		}

		return NetResult::Success;
	}

	NetResult TcpSocket::Set(bool value)
	{
		if (value == true) //Non-Blocking
		{
			unsigned long i = 1;
			int result = ioctlsocket(handle, FIONBIO, &i);

			if (result == SOCKET_ERROR)
			{
				int error = WSAGetLastError();
				Debug::Error("Failed to set newConnection as non Blocking: " + std::to_string(error));
				return NetResult::Error;
			}
		}

		if (value == false) //Blocking
		{
			unsigned long i = 0;
			int result = ioctlsocket(handle, FIONBIO, &i);

			if (result == SOCKET_ERROR)
			{
				int error = WSAGetLastError();
				Debug::Error("Failed to set newConnection as Blocking: " + std::to_string(error));
				return NetResult::Error;
			}
		}
		
		return NetResult::Success;
	}

	SOCKET TcpSocket::GetHandle()
	{
		return handle;
	}
}