#include <SDL/SDL.h>
#include <GL/glew.h>

#include "PlotterEngine.h"

namespace PlotterEngine {

	int init() {
		SDL_Init(SDL_INIT_EVERYTHING);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // ANTI-FLICKERING

		return 0;
	}

}