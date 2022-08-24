#include "Debug.h"

namespace Network
{
	NetworkException::NetworkException(std::string error)
	{
		Debug::Error(error);
	}

	std::string NetworkException::GetErrorString()
	{
		return error;
	}

	void Debug::Log(const std::string& line, const bool& log)
	{
		if (log == true)
		{
			WriteToFile("[Log]: " + line);
		}
		printf("[Log]: %s\n", line.c_str());
	}

	void Debug::Warning(const std::string& line, const bool& log)
	{
		if (log == true)
		{
			WriteToFile("[Warning]: " + line);
		}
		printf("[Warning]: %s\n", line.c_str());
	}

	void Debug::Error(const std::string& line, const bool& log)
	{
		if (log == true)
		{
			WriteToFile("[Error]: " + line);
		}
		printf("[Error]: %s\n", line.c_str());
	}

	void Debug::WriteToFile(const std::string& line)
	{
		//TODO:Implement writing to a file
	}
}