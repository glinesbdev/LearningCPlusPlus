#include "Logger.h"

void Logger::Write(const std::string& filename, const std::string& data)
{
	if (!ostream.is_open())
	{
		ostream.open(filename, std::ios_base::out | std::ios_base::app);
	}

	ostream << data;
}

Logger::~Logger()
{
	// Needed for safety?
	ostream.close();
}