#pragma once
#include <chrono>
namespace e
{
	class Chrono
	{
	public:
		//Starts the chrono
		Chrono();
		//Starts/resets the chrono
		void Set();
		//Reads the chrono
		float Get() const;
		//Reads and resets the chrono
		float GetSet();
	private:
		std::chrono::time_point<std::chrono::steady_clock> m_TimePoint;
	};
}