#include "EventManager.h"
#include "Event.h"
#include <SDL.h>

namespace helix
{
	int EventManager::PollEvent(Event &event)
	{
		SDL_Event sdl_event{};
		int poll_again{ SDL_PollEvent(&sdl_event) };
		switch (sdl_event.type)
		{
		case SDL_QUIT:
			event.type = Event::Type::_QUIT;
			break;
		case SDL_MOUSEMOTION:
			event.mouse_x = sdl_event.motion.x;
			event.mouse_y = sdl_event.motion.y;
			event.type = Event::Type::_MOUSEMOTION;
			break;
		case SDL_MOUSEBUTTONDOWN:
			event.button = sdl_event.button.button;
			event.type = Event::Type::_MOUSEBUTTONDOWN;
			break;
		case SDL_MOUSEBUTTONUP:
			event.button = sdl_event.button.button;
			event.type = Event::Type::_MOUSEBUTTONUP;
			break;
		case SDL_KEYDOWN:
			event.key = sdl_event.key.keysym.sym;
			event.type = Event::Type::_KEYDOWN;
			break;
		case SDL_KEYUP:
			event.key = sdl_event.key.keysym.sym;
			event.type = Event::Type::_KEYUP;
			break;
		}
		return poll_again;
	}
}

