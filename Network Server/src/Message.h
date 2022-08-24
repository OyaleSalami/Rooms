#pragma once
#include <string>
#include <stdint.h>

namespace Network
{
	///<summary>Inbuilt enum to identify the type of enum</summary>
	enum class Type:uint16_t
	{
		/// <summary>Identifies an authentication request</summary>
		auth = 1,
		/// <summary>Returned by the server/client if authentication failed</summary>
		authFailed,
		/// <summary>Identifies a chat message</summary>
		chat,
		/// <summary>Identifies a ping check message</summary>
		ping,
		/// <summary>Identifies a custom message</summary>
		custom
	};

	///<summary>Refers to the transport mode by which a message is to be sent</summary>
	enum class Mode:uint16_t
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

		Message();
		Message(const Type mode);
		Message(Message &message);
		Message(char* _data, const int &length);

		void Write(const char &value);
		void Write(const bool &value);
		void Write(const short &value);
		void Write(const int &value);
		void Write(const long &value);
		void Write(const float &value);
		void Write(const double &value);

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
		
	private:
		int readHead;
	};
}