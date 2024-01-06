#pragma once
#include <chrono>

class Timer
{
	static std::chrono::steady_clock::time_point m_prevTime;
	static std::chrono::nanoseconds m_elapsedTime;
	static double m_PlayTime_Seconds;
	static short m_PlayTime_Minute;
	static unsigned long long m_PlayTime_Hour;
public:

	static void Initialize();
	static void Update();
	static long long GetElapsedTimeMicro();
	static double GetPlayTimeSeconds();
	static short GetPlayTimeMinute();
	static unsigned long long GetPlayTimeHour();
};

