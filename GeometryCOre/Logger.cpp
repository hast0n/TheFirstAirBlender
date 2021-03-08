#include "Logger.h"

std::string Logger::_getFlag(LogLevel logLevel)
{
	std::string flag;

	switch (logLevel)
	{
	case LogLevel::INFO:
		flag = "[INFO] ";
		break;
	case LogLevel::WARNING:
		flag = "[WARNING] ";
		break;
	case LogLevel::FATAL:
		flag = "[FATAL] ";
		break;
	}

	return flag;
}

void Logger::Write(std::string message, LogLevel logLevel)
{
	std::cout << _getFlag(logLevel) << message << std::endl;
}