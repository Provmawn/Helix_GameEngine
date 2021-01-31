#include "Window.h"

#include <SDL_image.h>
#include <glad/glad.h>

#include "Exception.h"
namespace helix
{
	Window::Window()
	{
	}

	Window::~Window()
	{
	}

	int Window::Create(const std::string &title, int width, int height, unsigned int flag)
	{
		Uint32 flags{ SDL_WINDOW_OPENGL };
		if (flag & Window::Flag::INVISIBLE)
			flags |= SDL_WINDOW_HIDDEN;
		if (flag & Window::Flag::FULLSCREEN)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		if (flag & Window::Flag::BORDERLESS)
			flags |= SDL_WINDOW_BORDERLESS;

		// Initialize SDL


		m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (m_window == nullptr)
			throw Exception("SDL Window could not be created\n");

		SDL_GLContext gl_context{ SDL_GL_CreateContext(m_window) };
		if (gl_context == nullptr)
			throw Exception("SDL_GLContext could not be created\n");

		if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
			throw Exception("Failed to initiazlied sdl_image.h\n");

		if (!gladLoadGLLoader(static_cast<GLADloadproc>(SDL_GL_GetProcAddress)))
			throw Exception("Failed to initialize GLAD\n");

		std::printf("--- OpenGL Version: %s ---\n", glGetString(GL_VERSION));

		glClearColor(0.3f, 0.4f, 0.4f, 1.0f);

		// set vsync
		SDL_GL_SetSwapInterval(0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::SwapBuffers()
	{
		SDL_GL_SwapWindow(m_window);
	}
}
