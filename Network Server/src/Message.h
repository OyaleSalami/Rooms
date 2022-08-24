#pragma once
#include <string>
#include <stdint.h>

#include "Globals.h"
#include "Utility.h"


namespace Network
{
	using namespace Util;

	///<summary>Inbuilt enum to identify the type of enum</summary>
	enum class MessageType:uint16_t
	{
		/// <summary>Identifies an authentication request</summary>
		Auth = 1,
		/// <summary>Returned by the server/client if authentication failed</summary>
		AuthFailed,
		/// <summary>Identifies a chat message</summary>
		Chat,
		/// <summary>Identifies a ping check message</summary>
		Ping,
		/// <summary>Identifies a custom message</summary>
		Custom,
		Invalid
	};

	///<summary>Refers to the transport mode by which a message is to be sent</summary>
	enum class SendMode:uint16_t
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
		std::string buffer;
		MessageType type;

		//Message();
		Message(const MessageType &_type);
		Message(Message &message);
		Message(char* _data, const int &length);

		void Write(char &value);
		void Write(bool &value);
		void Write(short &value);
		void Write(int &value);
		void Write(long &value);
		void Write(float &value);
		void Write(double &value);

		void Read(char &value, const bool &moveHead = true);
		void Read(bool &value, const bool &moveHead = true);
		void Read(short &value, const bool &moveHead = true);
		void Read(int &value, const bool &moveHead = true);
		void Read(long &value, const bool &moveHead = true);
		void Read(float &value, const bool &moveHead = true);
		void Read(double &value, const bool &moveHead = true);

		void Length();
		void InsertLength();
		void ResetReadHead();
		void Clear(); 
		void Append(const void* data, uint32_t size);
		
	private:
		int readHead;
	};
}