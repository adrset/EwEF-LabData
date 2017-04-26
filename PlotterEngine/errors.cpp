#include <cstdlib>
#include "errors.h"

namespace PlotterEngine {

	void fatalError(std::string n) {
		std::cout << n << std::endl;

		getchar();
		SDL_Quit();
		exit(1);
	}
}