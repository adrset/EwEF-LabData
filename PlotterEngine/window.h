#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
namespace PlotterEngine {
	enum windowFlags { NONE = 0x0, HIDDEN = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class window
	{
	public:
		window();
		~window();

		int createWindow(std::string windowName, int screenWidth, int screenHeight, windowFlags flags);
		int getScreenW() { return _screenWidth; }
		int getScreenH() { return _screenHeight; }
		void swapBuffer();
	private:
		SDL_Window* _sdlWindow;
		int _screenWidth;
		int _screenHeight;
	};

}