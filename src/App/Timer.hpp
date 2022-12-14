#pragma once
#include <chrono>
class Timer
{
public:
    Timer();
    void start();
    void restart();
    float getElapsedTime();

private:
#ifdef _MSC_VER
    std::chrono::time_point<std::chrono::steady_clock> _start;
    std::chrono::time_point<std::chrono::steady_clock> _stop;
#endif

#ifdef __GNUC__
    std::chrono::time_point<std::chrono::system_clock> _start;
    std::chrono::time_point<std::chrono::system_clock> _stop;
#endif
};