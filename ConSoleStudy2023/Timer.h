#pragma once
#include <chrono>

class Timer
{
	std::chrono::steady_clock::time_point m_prevTime;
	std::chrono::nanoseconds m_elapsedTime;
	double m_PlayTime_Seconds;
	short m_PlayTime_Minute;
	unsigned long long m_PlayTime_Hour;
	int RenderX;
	int RenderY;

private:
	Timer() = default;
	Timer(const Timer&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(Timer&&) = delete;
	~Timer() = default;
public:
	static Timer& GetInstance();

	void Initialize();
	void Update();
	long long GetElapsedTimeMicro();
	double GetElapsedTimeSeconds();
	double GetPlayTimeSeconds();
	short GetPlayTimeMinute();
	unsigned long long GetPlayTimeHour();
	void RenderTimer();
};

