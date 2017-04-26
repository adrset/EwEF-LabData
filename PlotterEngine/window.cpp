#include "window.h"
#include "errors.h"

namespace PlotterEngine {

	window::window()
	{
	}


	window::~window()
	{
	}

	void window::swapBuffer() {
		SDL_GL_SwapWindow(_sdlWindow);
	}


	int window::createWindow(std::string windowName, int screenWidth, int screenHeight, windowFlags flags) {

		Uint32 allFlags = SDL_WINDOW_OPENGL;

		if (flags & FULLSCREEN) {
			allFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (flags & HIDDEN) {
			allFlags |= SDL_WINDOW_HIDDEN;
		}
		if (flags & BORDERLESS) {
			allFlags |= SDL_WINDOW_BORDERLESS;
		}

		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, allFlags);

		if (_sdlWindow == nullptr)
			fatalError("SDL window could not be created.");

		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);

		if (glContext == nullptr)
			fatalError("SDL_GL context could not be created.");

		GLenum error = glewInit();

		if (error != GLEW_OK)
			fatalError("GLEW error.");

		std::printf("*** OpenGL Version %s ***\n", glGetString(GL_VERSION));
	

		glClearColor(0.3f, 1.0f, 0.55f, 1.0f);

		SDL_GL_SetSwapInterval(0);//VSYNC OFF
		//alpha
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

}