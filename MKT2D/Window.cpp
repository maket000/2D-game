#include "Errors.h"
#include "Window.h"

namespace MKT2D {

	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {
		Uint32 flags = SDL_WINDOW_OPENGL;
		if (currentFlags & WN_INVISIBLE) {
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & WN_FULLSCREEN) {
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & WN_BORDERLESS) {
			flags |= SDL_WINDOW_BORDERLESS;
		}

		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_SDLWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
									  _screenWidth, _screenHeight, flags);
		if (!_SDLWindow) {
			fatalError("SDL window could not be created");
		}

		SDL_GLContext glContext = SDL_GL_CreateContext(_SDLWindow);
		if (!glContext) {
			fatalError("SDL_GL context could not be created");
		}

		GLenum error = glewInit();
		if (error != GLEW_OK) {
			fatalError("Could not initialize glew");
		}

		printf("openGL Version: %s\n", glGetString(GL_VERSION));

		SDL_GL_SetSwapInterval(0);
		glClearColor(1.0f, 0, 1.0f, 1.0f);

		return 0;
	}

	void Window::swapBuffer() {

		SDL_GL_SwapWindow(_SDLWindow);
	}

}