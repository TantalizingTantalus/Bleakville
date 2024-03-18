#include <string.h>
#include "spdlog/spdlog.h"

class Logging
{
public:
	static void LogInformation(std::string);
	static void LogWarning(std::string);
	static void LogError(std::string);

private:


};