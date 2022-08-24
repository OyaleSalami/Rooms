#include "Message.h"
#include <winsock.h>

namespace Network
{
	Message::Message(const MessageType &_type)
	{
		Clear(); //Reset the whole message 
		type = _type; //Set the Message type
	}

	Message::Message(char* data, const int& length)
	{
		Clear();

		if (length > MAX_MSG_SIZE)
		{
			throw NetworkException("[Message(char* data , const int& length)] - Data size exceeded max message size");
			return;
		}

		buffer.insert(buffer.end(), (char*)data, (char*)data + length);
	}

	void Message::Write(char &value)
	{
		//value = htonl(value);
		Append(&value, sizeof(char));
	}

	void Message::Write(bool& value)
	{
		//value = htons(value);
		Append(&value, sizeof(bool));
	}

	void Message::Write(short& value)
	{
		//value = htons(value);
		Append(&value, sizeof(short));
	}

	void Message::Write(int& value)
	{
		value = htons(value);
		Append(&value, sizeof(int));
	}

	void Message::Write(long& value)
	{
		value = htonl(value);
		Append(&value, sizeof(long));
	}

	void Message::Write(float& value)
	{
		//value = htonf(value);
		Append(&value, sizeof(float));
	}

	void Message::Write(double& value)
	{
		//value = htons(value);
		Append(&value, sizeof(double));
	}

	void Message::Append(const void* data, uint32_t size)
	{
		if (size > MAX_MSG_SIZE)
		{
			throw NetworkException("[Write(const void* data, uint32_t size)] - Data size exceeded max message size");
			return;
		}

		buffer.insert(buffer.end(), (char*)data, (char*)data + size);
	}

	void Message::Clear()
	{
		buffer.clear();
		type == MessageType::Invalid;
		readHead = 0;
	}
}