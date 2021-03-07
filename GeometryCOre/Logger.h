#pragma once
#include <iostream>

enum class LogLevel { INFO = 0, WARNING = 1, FATAL = 2 };

class Logger
{
	static std::string _getFlag(LogLevel logLevel);
	Logger() = delete;
	~Logger() = delete;

public:
	static void Write(std::string message, LogLevel logLevel);
};
