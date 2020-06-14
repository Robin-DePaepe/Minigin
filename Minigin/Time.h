#pragma once
#include "Singleton.h"
#include <chrono>

namespace minigin
{
	using namespace std;
	using namespace chrono;

	class Time final : public Singleton<Time>
	{
	public:
		//rule of 5
		Time();
		~Time() = default;

		Time(const Time& other) = delete;
		Time(Time&& other) = delete;
		Time& operator=(const Time& other) = delete;
		Time& operator=(Time&& other) = delete;

		//functions
		void Update();

		float GetElapsedTime() const;
		unsigned int GetFPS() const;

	private:
		//datamembers
		float m_ElapsedTime, m_FPSTimer;
		unsigned int m_FPS;
		unsigned int m_FPSCount;

		time_point<steady_clock> m_PreviousTime;
	};
}
