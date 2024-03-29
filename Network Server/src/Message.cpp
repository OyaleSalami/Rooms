#include "Message.h"

namespace Network
{
	Message::Message()
	{
		Clear();
	}

	Message::Message(const MessageType &_type)
	{
		Clear(); //Reset the whole message
		Write((int)type);
		type = _type; //Set the Message type
	}

	Message::Message(char* data, const int& length)
	{
		Clear();

		if (length > MAX_MSG_SIZE)
		{
			throw NetworkException("Data exceeded max message size");
			return;
		}

		buffer.insert(buffer.end(), (char*)data, (char*)data + length);
	}

	#pragma region Writing Functions

	void Message::Write(const char &value)
	{
		//value = htonl(value);
		Append(&value, sizeof(char));
	}

	void Message::Write(const bool& value)
	{
		//value = htons(value);
		Append(&value, sizeof(bool));
	}

	void Message::Write(const short& value)
	{
		//value = htons(value);
		Append(&value, sizeof(short));
	}

	void Message::Write(const int& value)
	{
		//value = htons(value);
		Append(&value, sizeof(int));
	}

	void Message::Write(const long& value)
	{
		//value = htonl(value);
		Append(&value, sizeof(long));
	}

	void Message::Write(const float& value)
	{
		//value = htonf(value);
		Append(&value, sizeof(float));
	}

	void Message::Write(const double& value)
	{
		//value = htons(value);
		Append(&value, sizeof(double));
	}

	void Message::Write(const std::string &value)
	{
		int size = value.length();
		//value = htons(value);
		Append(&size, sizeof(int)); //Append the size of the string first

		for (int i = 0; i < size; i++)
		{
			Write(value[i]); //Then append the string per character
		}
	}

	void Message::Append(const void* data, uint32_t size)
	{
		if (size > MAX_MSG_SIZE)
		{
			throw NetworkException("Data to be appended exceeded max message size");
			return;
		}

		buffer.insert(buffer.end(), (char*)data, (char*)data + size);
	}

	#pragma endregion For Writing to a message

	#pragma region Reading Functions

	void Message::Read(char& value, const bool& moveHead)
	{
		value = buffer[readHead];
		if (moveHead == true)
		{
			readHead = readHead + sizeof(char);
		}
	}

	void Message::Read(bool& value, const bool& moveHead)
	{
		value = (bool)buffer[readHead];
		if (moveHead == true)
		{
			readHead = readHead + sizeof(bool);
		}
	}

	void Message::Read(short& value, const bool& moveHead)
	{
		value = (short)buffer[readHead];
		if (moveHead == true)
		{
			readHead = readHead + sizeof(short);
		}
	}

	void Message::Read(int& value, const bool& moveHead)
	{
		value = (int)buffer[readHead];
		if (moveHead == true)
		{
			readHead = readHead + sizeof(int);
		}
	}

	void Message::Read(long& value, const bool& moveHead)
	{
		value = (long)buffer[readHead];
		if (moveHead == true)
		{
			readHead = readHead + sizeof(long);
		}
	}

	void Message::Read(float& value, const bool& moveHead)
	{
		value = (float)buffer[readHead];
		if (moveHead == true)
		{
			readHead = readHead + sizeof(float);
		}
	}

	void Message::Read(double& value, const bool& moveHead)
	{
		value = (double)buffer[readHead];
		if (moveHead == true)
		{
			readHead = readHead + sizeof(double);
		}
	}

	void Message::Read(std::string &value, const bool& moveHead)
	{
		int size;
		Read(size);

		value.resize(size);

		for (int i = 0; i < size; i++)
		{
			value[i] = buffer[readHead + i];
		}

		if (moveHead == true)
		{
			readHead = readHead + sizeof(size);
		}
	}

	#pragma endregion For Reading from a message

	void Message::InsertLength()
	{
		if (sealed != true)
		{
			int len = buffer.size();

			buffer.insert(buffer.begin(), (char*)&len, (char*)&len + 4);
			//At the beginning of the array
			//pointer to the start at len
			//pointer to the stop at len + 4 (hopefully)
			sealed == true;
		}
		else
		{
			Debug::Warning("You are trying to write to a sealed message");
		}
	}

	int Message::Length()
	{
		return buffer.size();
	}

	void Message::ResetReadHead()
	{
		readHead = 0;
	}

	void Message::Clear()
	{
		buffer.clear();
		ResetReadHead();
	}

	bool Message::Handle()
	{
		try
		{
			int type;
			Read(type); //Read out the packet's type
			Debug::Log("Type of message: " + std::to_string(type));

			if (type == (int)MessageType::Chat)
			{
				std::string chat;
				Read(chat);

				Debug::Log("Chat from client: " + chat);
				return true;
			}
			if (type == (int)MessageType::Position)
			{
				std::string chat;
				Read(chat);

				Debug::Log("Chat from client: " + chat);
				return true;
			}

		}
		catch (...)
		{
			Debug::Error("Unable to handle the message");
			return false;
		}
		return false;
	}
}