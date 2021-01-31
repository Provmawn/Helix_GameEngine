#include "Helix.h"

#include <SDL.h>
#include <glad/glad.h>
namespace helix 
{
	void Init()
	{
		SDL_Init(SDL_INIT_EVERYTHING);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	}
}
