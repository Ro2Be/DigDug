#include "MiniginPCH.h"
#include "EventNotifier.h"
#include "EventObserver.h"

namespace e
{
	using namespace std;

	void EventNotifier::Notify(const Event& event)
	{
		for (EventObserver* pObserver : m_pObservers) pObserver->Observe(event);
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