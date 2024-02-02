#pragma once
#include <iostream>
#include <spdlog/spdlog.h>

class Logger
{
public:
	static void LogInformation(const std::string&);
	static void LogWarning(const std::string&);
	static void LogError(const std::string&);

};