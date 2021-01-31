#ifndef WINDOW_H
#define WINDOW_H
#include <SDL.h>
#include <string>
namespace helix
{
	class Window
	{
	public:
		enum Flag
		{
			DEFAULT = 0x0,
			INVISIBLE = 0x1,
			FULLSCREEN = 0x2,
			BORDERLESS = 0x3,
		};
		Window();
		~Window();

		int Create(const std::string &title, int width, int height, unsigned int flag);
		void SwapBuffers();

		int GetScreenWidth() const { return m_width; }
		int GetScreenHeight() const { return m_height; }

	private:
		SDL_Window *m_window{};
		int m_width{};
		int m_height{};
	};
}
#endif

