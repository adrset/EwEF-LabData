#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// Tested on:
// 1. Visual Studio 2012 on Windows
// 2. Mingw gcc 4.7.1 on Windows
// 3. gcc 4.6.3 on GNU/Linux

// Note that gnuplot binary must be on the path
// and on Windows we need to use the piped version of gnuplot
#ifdef WIN32
#define GNUPLOT_NAME "pgnuplot -persist"
#else 
#define GNUPLOT_NAME "gnuplot"
#endif

int main()
{
#ifdef WIN32
	FILE *pipe = _popen(GNUPLOT_NAME, "w");
#else
	FILE *pipe = popen(GNUPLOT_NAME, "w");
#endif

	if (pipe != NULL)
	{
		fprintf(pipe, "set term wx\n");         // set the terminal
		fprintf(pipe, "plot '-' with lines\n"); // plot type
		for (int i = 0; i < 10; i++)             // loop over the data [0,...,9]
			fprintf(pipe, "%d\n", i);           // data terminated with \n
		fprintf(pipe, "%s\n", "e");             // termination character
		fflush(pipe);                           // flush the pipe

												// wait for key press
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin.get();

#ifdef WIN32
		_pclose(pipe);
#else
		pclose(pipe);
#endif
	}
	else
		std::cout << "Could not open pipe" << std::endl;
	return 0;
}