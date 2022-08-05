#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

class Logger
{
public:
	Logger() = default;

	// Copy policy
	Logger(const Logger& copy) = delete;
	Logger& operator=(const Logger& copy) = delete;

	// Move policy
	Logger(Logger&& move) = delete;
	Logger& operator=(Logger&& move) = delete;

	~Logger();

public:
	void Write(const std::string& filename, const std::string& data);

private:
	std::ofstream ostream{};
};

#endif