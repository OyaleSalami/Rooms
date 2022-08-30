#include "TCP.h"

namespace Network
{
	TcpSocket::TcpSocket(SOCKET _handle)
	{
		handle = _handle;
	}

	NetResult TcpSocket::Create()
	{
		if (handle != INVALID_SOCKET)
		{
			return NetResult::Error;
		}

		//Attempt to create a TCP socket IPv4
		handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (handle == INVALID_SOCKET)
		{
			int error = WSAGetLastError();
			return NetResult::Error;
		}

		//TODO: Disable Nagles algorithm for TCP Sockets
		return NetResult::Success;
	}

	NetResult TcpSocket::Close()
	{
		if (handle = INVALID_SOCKET)
		{
			return NetResult::Error;
		}

		int result = closesocket(handle);

		if (result != 0) //an error why trying to close the socket
		{
			return NetResult::Error;
		}

		handle = INVALID_SOCKET;
		return NetResult::Success;
	}

	NetResult TcpSocket::Bind(Endpoint endpoint)
	{
		if (endpoint.GetIPVersion() == IPVersion::Invalid)
		{
			return NetResult::Error;
		}

		sockaddr_in addr = endpoint.GetSockaddrIPv4();
		int result = bind(handle, (sockaddr*)&addr, sizeof(sockaddr_in));

		if (result != 0)
		{
			int error = WSAGetLastError();
			Debug::Error("Error while binding: ");
			return NetResult::Error;
		}

		return NetResult::Success;
	}

	NetResult TcpSocket::Listen(Endpoint endpoint, int backlog)
	{
		//Backlog is the pending connections
		if (Bind(endpoint) != NetResult::Success)
		{
			return NetResult::Error;
		}

		int result = listen(handle, backlog);

		if (result != 0)
		{
			int error = WSAGetLastError();
			Debug::Error("Error while listening: " + error);

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
		bytesSent = send(handle, (const char*)data, numberOfBytes, NULL);

		if (bytesSent == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			return NetResult::Error;
		}
		return NetResult::Success;
	}

	NetResult TcpSocket::Recv(void* destination, int numberOfBytes, int& bytesReceived)
	{
		bytesReceived = recv(handle, (char*)destination, numberOfBytes, NULL);
		if (bytesReceived == 0) //Connection closed gracefully
		{
			return NetResult::Error;
		}

		if (bytesReceived == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
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
		uint16_t encodedMessageSize = htons(message.buffer.size());

		NetResult result = SendAll(&encodedMessageSize, sizeof(uint16_t));
		if (result != NetResult::Success)
			return NetResult::Error;

		result = SendAll(message.buffer.data(), message.buffer.size());
		if (result != NetResult::Success)
			return NetResult::Error;

		return NetResult::Success;
	}

	NetResult TcpSocket::Recv(Message& message)
	{
		message.Clear();
		uint16_t encodedSize = 0;

		NetResult result = RecvAll(&encodedSize, sizeof(uint16_t));
		if (result != NetResult::Success)
			return NetResult::Error;

		uint16_t bufferSize = ntohs(encodedSize);
		if (bufferSize > MAX_MSG_SIZE)
			return NetResult::Error;

		message.buffer.resize(bufferSize);
		result = RecvAll(&message.buffer[0], bufferSize);
		if (result != NetResult::Success)
			return NetResult::Error;

		return NetResult::Success;
	}

	SOCKET TcpSocket::GetHandle()
	{
		return handle;
	}
}