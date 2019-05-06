#include "MiniginPCH.h"
#include "Chrono.h"

namespace e
{
	using namespace std;
	Chrono::Chrono():
		m_TimePoint{ chrono::high_resolution_clock::now() }
	{
	}
	void Chrono::Set()
	{
		m_TimePoint = chrono::high_resolution_clock::now();
	}
	float Chrono::Get() const
	{
		return chrono::duration<float, milli>(chrono::high_resolution_clock::now() - m_TimePoint).count();
	}
	float Chrono::GetSet()
	{
		const chrono::time_point<chrono::steady_clock> now{ chrono::high_resolution_clock::now() };
		const float time{ chrono::duration<float, milli>(now - m_TimePoint).count() };
		m_TimePoint = now;
		return time;
	}
}