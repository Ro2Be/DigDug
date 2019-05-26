#pragma once
namespace e
{
	struct Event;
	class EventObserver abstract
	{
	public:
		virtual ~EventObserver() = default;
		virtual void Observe(const Event* pEvent) = 0;
	};
}