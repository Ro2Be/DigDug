#include "MiniginPCH.h"
#include "Event.h"

namespace e
{
	using namespace std;

	void EventNotifier::Notify(Event* pEvent)
	{
		for (EventObserver* pObserver : m_pObservers) pObserver->Observe(pEvent);
		delete pEvent;
	}
	void EventNotifier::AddObserver(EventObserver* pObserver)
	{
		m_pObservers.push_back(pObserver);
	}
	void EventNotifier::RemoveObserver(EventObserver* pObserver)
	{
		experimental::erase(m_pObservers, pObserver);
	}
}