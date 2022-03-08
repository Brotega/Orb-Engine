#include "Timer.h"
#include <SDL2/SDL.h>

namespace OrbEngine
{
	Timer::Timer()
	{
		m_Start = static_cast<float>(SDL_GetTicks());
	}

	Timer::~Timer()
	{
		float end = static_cast<float>(SDL_GetTicks());
		float duration = end - m_Start;

		SDL_Log("Time passed: %f\n", duration);
	}
}