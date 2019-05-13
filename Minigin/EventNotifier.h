#pragma once
namespace e
{
	class Event;
	class EventObserver;
	class EventNotifier
	{
	public:
		EventNotifier() = default;
		void AddObserver(EventObserver* pObserver);
		void RemoveObserver(EventObserver* pObserver);
		void Notify(const Event& event);
	private:
		std::vector<EventObserver*> m_pObservers;
	};
}