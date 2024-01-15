#include "Timer.h"
#include <iostream>

Timer* Timer::GetInstance()
{
	static Timer* instance = new Timer();
	return instance;
}

void Timer::Initialize()
{
	m_prevTime = std::chrono::high_resolution_clock::now();
}

void Timer::Update()
{
	auto now = std::chrono::high_resolution_clock::now();
	m_elapsedTime = now - m_prevTime;
	m_prevTime = now;

	m_PlayTime_Seconds += std::chrono::duration_cast<std::chrono::microseconds>(m_elapsedTime).count() / 100;
	if (m_PlayTime_Seconds >= 60'0000) {
		m_PlayTime_Seconds = 0.0;
		++m_PlayTime_Minute;
	}
	if (m_PlayTime_Minute >= 60) {
		m_PlayTime_Minute = 0.0;
		++m_PlayTime_Hour;
	}
}

long long Timer::GetElapsedTimeMicro()
{
	return std::chrono::duration_cast<std::chrono::microseconds>(m_elapsedTime).count();
}

double Timer::GetElapsedTimeSeconds()
{
	return (double)GetElapsedTimeMicro() / 1'000'000;
}

double Timer::GetPlayTimeSeconds()
{
	return m_PlayTime_Seconds / 10000;
}

short Timer::GetPlayTimeMinute()
{
	return m_PlayTime_Minute;
}

unsigned long long Timer::GetPlayTimeHour()
{
	return m_PlayTime_Hour;
}

void Timer::RenderTimer()
{
	std::cout << "                     PlayTime : " << m_PlayTime_Hour << " h  ";
	std::cout << m_PlayTime_Minute << " m  ";
	std::cout << m_PlayTime_Seconds / 10000 << "  s  " << std::endl;
	std::cout << std::fixed;
	std::cout.precision(1);
	std::cout << "                     fps      : " << 1.0 / GetElapsedTimeSeconds() << "\tfps" << std::endl;
	std::cout.unsetf(std::ios::scientific);
	std::cout.precision(4);
}
