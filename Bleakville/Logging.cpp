#include "Logging.h"

void Logging::LogInformation(std::string Message)
{
	spdlog::info(Message);
}

void Logging::LogWarning(std::string Message)
{
	spdlog::warn(Message);
}

void Logging::LogError(std::string Message)
{
	spdlog::error(Message);
}