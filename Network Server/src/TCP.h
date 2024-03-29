#pragma once

#include "Endpoint.h"
#include "Message.h"
#include "Globals.h"
#include "MessageHandler.h"

using namespace Network::Util;

namespace Network
{
	///<summary>Class abstraction for a TCP Socket</summary>
	class TcpSocket
	{
	public:
		SOCKET handle = INVALID_SOCKET;

		TcpSocket(const SOCKET& = INVALID_SOCKET);
		NetResult Create();
		NetResult Close();
		NetResult Bind(Endpoint endpoint);
		NetResult Listen(Endpoint endpoint, int backlog = 5);
		NetResult Accept(TcpSocket& outSocket);
		NetResult Connect(Endpoint endpoint);
		NetResult Send(const void* data, int numberOfBytes, int& bytesSent);
		NetResult Recv(void* destination, int numberOfBytes, int& bytesReceived);
		NetResult SendAll(const void* data, int numberOfBytes);
		NetResult RecvAll(void* destination, int numberOfBytes);
		NetResult Recv(Message& message);
		NetResult Send(Message& message);
		/// <summary>Sets the socket's blocking state</summary>
		/// <param name="value">True: Non-Blocking, False: Blocking</param>
		NetResult Set(bool value);
		SOCKET GetHandle();
	};
}