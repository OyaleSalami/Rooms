#pragma once
#include <stdio.h>
#include <fstream>
#include <string>

namespace Network
{
	class Debug
	{
	public:
		static bool logToFile;
		static std::string path;
		static std::string filename;

		static void Log(const std::string& line, const bool &log = true)
		{
			if (log == true)
			{
				WriteToFile("[Log]: " + line);
			}
			printf("[Log]: %s\n", line.c_str());
		}

		static void Warning(const std::string& line, const bool& log = true)
		{
			if (log == true)
			{
				WriteToFile("[Warning]: " + line);
			}
			printf("[Warning]: %s\n", line.c_str());
		}

		static void Error(const std::string& line, const bool& log = true)
		{
			if (log == true)
			{
				WriteToFile("[Error]: " + line);
			}
			printf("[Error]: %s\n", line.c_str());
		}

		static void WriteToFile(const std::string& line)
		{
			//TODO:Implement writing to a file
		}
	};
}