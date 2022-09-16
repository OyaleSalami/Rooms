#pragma once
#include "Message.h"
#include "Debug.h"

namespace Network
{
	static void DefaultHandleData(Message& message)
	{
		std::string text;
		message.Read(text);

		Debug::Log("Message Received: ");
		Debug::Log(text);
	}
}