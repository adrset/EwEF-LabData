#include <iostream>
#include "gnuplot.h"

gnuplot::gnuplot() {

}
gnuplot::~gnuplot() {

}
void gnuplot::plot(std::vector<std::string> commands) {
#ifdef WIN32
	FILE* p = _popen("gnuplot.exe", "w");
#else
	FILE* p = popen("gnuplot -persist", "w");
#endif

	for (std::string& it : commands) {
		fprintf(p, it.c_str());
	}
	fflush(p);
	if (p != nullptr) {




#ifdef WIN32
		_pclose(p);
#else
		pclose(p);
#endif
	}
	else {
		std::cout << "Nie mozna otowrzyc gnuplota :( " << std::endl;
	}

}