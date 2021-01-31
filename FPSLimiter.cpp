#include "FPSLimiter.h"
#include <SDL.h>
namespace helix
{
	FPSLimiter::FPSLimiter()
	{
	}

	FPSLimiter::~FPSLimiter()
	{
	}

	void FPSLimiter::Init(FPS_t max_fps)
	{
		SetMaxFPS(max_fps);
	}

	void FPSLimiter::SetMaxFPS(FPS_t max_fps)
	{
		m_max_fps = max_fps;
	}

	void FPSLimiter::Begin()
	{
		m_start_ticks = SDL_GetTicks();
	}

	FPSLimiter::FPS_t FPSLimiter::End()
	{
		CalculateFPS();

		unsigned int ticks{ SDL_GetTicks() - m_start_ticks };
		float miliseconds_per_frame{ 1000.0f / m_max_fps };
		if (ticks < miliseconds_per_frame)
			SDL_Delay(miliseconds_per_frame - static_cast<float>(ticks));


		return m_fps;
	}
	void FPSLimiter::CalculateFPS()
	{
		static constexpr int SAMPLES{ 10 };
		static unsigned int frametimes[SAMPLES]{};
		static int frametimes_pos{ 0 };
		static unsigned int previous_ticks{ SDL_GetTicks() };

		unsigned int current_ticks{ SDL_GetTicks() };

		m_frametime = current_ticks - previous_ticks;
		frametimes[frametimes_pos % SAMPLES] = m_frametime;
		++frametimes_pos;

		previous_ticks = current_ticks;

		int count{};
		if (frametimes_pos < SAMPLES)
			count = frametimes_pos;
		else
			count = SAMPLES;

		float frametime_average{ 0 };
		for (int i{ 0 }; i < count; ++i)
		{
			frametime_average += frametimes[i];
		}
		frametime_average /= count;

		if (frametime_average > 0)
			m_fps = 1000.0f / frametime_average;
	}
}
