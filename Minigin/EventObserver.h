#pragma once
namespace e
{
	struct Event;
	class EventObserver abstract
	{
	public:
		virtual ~EventObserver() = 0;;
		virtual void Observe(const Event& event) = 0;
	};
}