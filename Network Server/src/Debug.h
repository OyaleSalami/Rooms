#pragma once
#include <iostream>
#include <fstream>
#include <string>

namespace Network
{
	class Debug
	{
	public:
		static std::string path;
		static std::string filename;

		static void Log(const std::string& line)
		{
			WriteToFile(line);
			std::cout << "[Log]: " << line << std::endl;
		}

		static void Warning(const std::string& line)
		{
			WriteToFile(line);
			std::cout << "[Warning]: " << line << std::endl;
		}

		static void Error(const std::string& line)
		{
			WriteToFile(line);
			std::cout << "[Error]: " << line << std::endl;
		}

		static void WriteToFile(const std::string& line)
		{
			//TODO:Implement writing to a file
		}
	};
}