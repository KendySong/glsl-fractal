#include "Timer.hpp"

Timer::Timer()
{
	this->start();
}

void Timer::start()
{
	_start = std::chrono::high_resolution_clock::now();
}

void Timer::restart()
{
	this->start();
}

float Timer::getElapsedTime()
{
	_stop = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(_stop - _start).count() * 0.000001;
}