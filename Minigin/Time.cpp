#include "MiniginPCH.h"
#include "Time.h"

Time::Time()
	:m_PreviousTime{ high_resolution_clock::now()}
	,m_ElapsedTime{}
	,m_FPSTimer{}
	, m_FPS{}
	,m_FPSCount{}
{
}

void Time::Update()
{
	const auto currentTime = high_resolution_clock::now();
	m_ElapsedTime = float(duration_cast<milliseconds>(currentTime - m_PreviousTime).count());

	m_PreviousTime = currentTime;

	m_FPSTimer += m_ElapsedTime;
	++m_FPSCount;

	//update FPS
	if (m_FPSTimer >= 1000.f) //in miliseconds
	{
		m_FPSTimer -= 1000.f;
		m_FPS = m_FPSCount;
		m_FPSCount = 0;
	}
}

unsigned int Time::GetFPS() const
{
	return m_FPS;
}

float Time::GetElapsedTime() const
{
	return m_ElapsedTime / 1000.f;//return in seconds
}
