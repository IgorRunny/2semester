#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>



namespace mrLogger
{
	enum class LogLevel
	{
		DEBUG,
		RELEASE
	};

	enum class LogType
	{
		INFO,
		DEBUG,
		ERROR
	};

	class Log
	{
	private:
		static std::ofstream i_report;
		static LogLevel i_level;
	public:
		Log(LogLevel level) 
		{
			i_level = level;
			i_report.open("log.txt");
		}


		static void Report(LogType type, const std::string& report)
		{
			auto time = std::time(nullptr);
			std::string tmp;
			switch (type)
			{
			case mrLogger::LogType::INFO:
				tmp = "[INFO]" + report;
				break;
			case mrLogger::LogType::DEBUG:
				if (i_level != mrLogger::LogLevel::DEBUG)
					return;
				tmp = "[DEBUG]" + report;
				break;
			case mrLogger::LogType::ERROR:
				tmp = "!ERROR!" + report;
				break;
			default:
				break;
			}

			if (i_level == mrLogger::LogLevel::DEBUG)
				std::cerr << tmp << "\t" << "[" << std::put_time(std::localtime(&time), "%T") << "]" << "\n";
			i_report << tmp << "\t" << "[" << std::put_time(std::localtime(&time), "%T") << "]" << "\n";
			i_report.flush();
		}


		~Log()
		{

		}
	};
}