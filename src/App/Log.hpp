#pragma once
#include <fstream>
#include <windows.h>

#include "ConsoleColor.hpp"

class Log
{
private:
	Log();

public:
	static Log* instance() noexcept;

	void log(std::string log, int color = 15);

private:
	static Log* s_log;
	HANDLE m_hConsole;
	std::ofstream m_logStream;
};