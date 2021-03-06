#pragma once
namespace e
{
	struct Event;
	class EventObserver;
	class EventNotifier final
	{
	public:
		EventNotifier() = default;
		void AddObserver(EventObserver* pObserver);
		void RemoveObserver(EventObserver* pObserver);
		void Notify(Event* pEvent);
	private:
		std::vector<EventObserver*> m_pObservers;
	};
}