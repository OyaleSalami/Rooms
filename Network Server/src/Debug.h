#pragma once
#include <stdio.h>
#include <fstream>
#include <string>

namespace Network
{
	class NetworkException
	{
	public:
		NetworkException(std::string error);
		std::string GetErrorString();

	private:
		std::string error;
	};

	class Debug
	{
	public:
		static std::string path;
		static std::string filename;

		static void Log(const std::string& line, const bool& log = true);
		static void Warning(const std::string& line, const bool& log = true);
		static void Error(const std::string& line, const bool& log = true);
		static void WriteToFile(const std::string& line);
	};
}