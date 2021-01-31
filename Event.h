#ifndef EVENT_H
#define EVENT_H
#include <SDL.h>
namespace helix
{
	struct Event
	{
		enum class Type
		{
			_QUIT = SDL_QUIT,
			_MOUSEMOTION = SDL_MOUSEMOTION,
			_MOUSEBUTTONDOWN = SDL_MOUSEBUTTONDOWN,
			_MOUSEBUTTONUP = SDL_MOUSEBUTTONUP,
			_KEYDOWN = SDL_KEYDOWN,
			_KEYUP = SDL_KEYUP
		};
		enum class Key
		{
			_0 = SDLK_0,
			_1 = SDLK_1,
			_2 = SDLK_2,
			_3 = SDLK_3,
			_4 = SDLK_4,
			_5 = SDLK_5,
			_6 = SDLK_6,
			_7 = SDLK_7,
			_8 = SDLK_8,
			_9 = SDLK_9,
			_a = SDLK_a,
			_b = SDLK_b,
			_c = SDLK_c,
			_d = SDLK_d,
			_e = SDLK_e,
			_f = SDLK_f,
			_g = SDLK_g,
			_h = SDLK_h,
			_i = SDLK_i,
			_j = SDLK_j,
			_k = SDLK_k,
			_l = SDLK_l,
			_m = SDLK_m,
			_n = SDLK_n,
			_o = SDLK_o,
			_p = SDLK_p,
			_q = SDLK_q,
			_r = SDLK_r,
			_s = SDLK_s,
			_t = SDLK_t,
			_u = SDLK_u,
			_v = SDLK_v,
			_w = SDLK_w,
			_x = SDLK_x,
			_y = SDLK_y,
			_z = SDLK_z,
		};
		enum class Mouse
		{
			_BUTTONLEFT = SDL_BUTTON_LEFT,
			_BUTTONMIDDLE = SDL_BUTTON_MIDDLE,
			_BUTTONRIGHT = SDL_BUTTON_RIGHT,
		};
		Type type{};
		float mouse_x{};
		float mouse_y{};
		unsigned int button{};
		unsigned int key{};
	};
}
#endif