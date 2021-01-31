#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "Event.h"

namespace helix
{
	class EventManager
	{
	public:
		EventManager() = default;
		~EventManager() = default;
		int PollEvent(Event &event);
	};
}
#endif
