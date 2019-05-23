#pragma once
#include "EventNotifier.h"
#include "EventObserver.h"

namespace e
{
	struct Event abstract
	{
		virtual ~Event() = 0;
	};
}