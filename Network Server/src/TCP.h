#pragma once

#include <thread>
#include <future>


#include "Endpoint.h"
#include "Message.h"
#include "Globals.h"

using namespace Network::Util;

namespace Network
{
	///<summary>Class abstraction for a TCP Socket</summary>
	class TcpSocket
	{
	public:
		SOCKET handle = INVALID_SOCKET;

		TcpSocket(SOCKET = INVALID_SOCKET);
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
		SOCKET GetHandle();

	private:
		int id;
		//std::thread listen_thread(Listen, Endpoint, int);
	};
}