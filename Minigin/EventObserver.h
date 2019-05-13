#pragma once
class Event;

namespace e
{
	class EventObserver
	{
	public:
		virtual ~EventObserver() = default;;
		virtual void Observe(const Event& event) = 0;
	};
}