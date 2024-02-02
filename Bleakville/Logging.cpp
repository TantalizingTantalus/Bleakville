#include "Logging.h"

void Logger::LogInformation(const std::string& Input)
{
	spdlog::info(Input);
	return;
}

void Logger::LogWarning(const std::string& Input)
{
	spdlog::warn(Input);
	return;
}

void Logger::LogError(const std::string& Input)
{
	spdlog::error(Input);
	return;
}