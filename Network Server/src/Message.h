#pragma once

//#define WIN32_LEAN_AND_MEAN
//#include <winsock.h>

#include <string>
#include <stdint.h>

#include "Globals.h"
#include "Utility.h"


namespace Network
{
	using namespace Util;

	///<summary>Inbuilt enum to identify the type of message</summary>
	enum class MessageType:uint16_t
	{
		/// <summary>Identifies a chat message</summary>
		Chat = 1,
		/// <summary>Identifies an authentication request</summary>
		Auth,
		/// <summary>Returned by the server/client if authentication failed</summary>
		AuthFailed,
		/// <summary>Identifies a ping check message</summary>
		Ping,
		/// <summary>Identifies a custom message</summary>
		Custom,
		Invalid
	};

	///<summary>Transport mode by which a message is to be sent</summary>
	enum class SendMode
	{
		/// <summary>A message to be broadcasted</summary>
		Multicast = 1,
		/// <summary>A message to be sent over TCP</summary>
		Tcp,
		/// <summary>A message to be sent over UDP(Unreliable)</summary>
		Udp,
		/// <summary>A message to be sent over UDP(Reliable)</summary>
		Reliable
	};


	class Message
	{
	public:
		MessageType type;
		std::string buffer = "";

		//Message Constructors();
		Message();
		Message(const MessageType &_type);
		Message(char* _data, const int &length);

		void Write(const char &value);
		void Write(const bool &value);
		void Write(const short &value);
		void Write(const int &value);
		void Write(const long &value);
		void Write(const float &value);
		void Write(const double &value);
		void Write(const std::string &value);

		void Read(char &value, const bool &moveHead = true);
		void Read(bool &value, const bool &moveHead = true);
		void Read(short &value, const bool &moveHead = true);
		void Read(int &value, const bool &moveHead = true);
		void Read(long &value, const bool &moveHead = true);
		void Read(float &value, const bool &moveHead = true);
		void Read(double &value, const bool &moveHead = true);
		void Read(std::string &value, const bool& moveHead = true);

		void Length();
		void InsertLength();
		void ResetReadHead();
		void Clear(); 
		void Append(const void* data, uint32_t size);
		
	private:
		int readHead;
	};
}