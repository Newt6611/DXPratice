#include "Timer.h"
#include <Windows.h>
#include "Log.h"

float Timer::DeltaTime;
int Timer::FPS;

Timer::Timer()
{
	m_PreTime = 0;
	m_FPS = 0;
	m_FPS_BTW = 0;
	mc_FPS = 0;
}

Timer::~Timer()
{
}

void Timer::Update()
{
	__int64 currentTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	m_SecondsPerCount = 1.0 / (double)countsPerSec;

	m_DeltaTime = (currentTime - m_PreTime) * m_SecondsPerCount;

	if (m_DeltaTime < 0)
		m_DeltaTime = 0;

	m_PreTime = currentTime;


	// fps
	if (m_FPS_BTW >= 1)
	{
		m_FPS = mc_FPS;
		m_FPS_BTW = 0;
		mc_FPS = 0;
	}
	else
	{
		m_FPS_BTW += m_DeltaTime;
		mc_FPS++;
	}

	DeltaTime = m_DeltaTime;
	FPS = m_FPS;
}
