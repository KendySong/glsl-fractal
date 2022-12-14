#include <iostream>
#include "Log.hpp"

Log* Log::s_log = nullptr;

Log::Log()
{
	m_logStream = std::ofstream("log.txt", std::ios::app);
	if (!m_logStream.is_open())
	{
		std::cout << "[ERROR] log.txt cannot be open";
	}

	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

Log* Log::instance() noexcept
{
	if (s_log == nullptr)
	{
		s_log = new Log();
	}
	return s_log;
}

void Log::log(std::string log, int color)
{
	SetConsoleTextAttribute(m_hConsole, color);
	std::cout << log;
	SetConsoleTextAttribute(m_hConsole, 15);

	m_logStream << log;
}