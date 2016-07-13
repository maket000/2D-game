#pragma once

#include <GL/glew.h>
#include <SDL/SDL.h>
#include <string>

namespace MKT2D {

	enum WindowFlags {
		WN_INVISIBLE = 0x1,
		WN_FULLSCREEN = 0x2,
		WN_BORDERLESS = 0x4
	};

	class Window
	{
	public:
		Window();
		~Window();

		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

		void swapBuffer();

		int getScreenWidth() { _screenWidth; }
		int getScreenHeight() { _screenHeight; }

	private:
		SDL_Window *_SDLWindow;
		int _screenWidth;
		int _screenHeight;
	};

}