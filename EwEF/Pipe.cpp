#include "Pipe.h"



Pipe::Pipe()
{
	m_pipe = nullptr;
}


Pipe::~Pipe()
{
	
}

void Pipe::init() {
#ifdef WIN32
	_popen(GNUPLOT_NAME , "w");
#else
	popen(GNUPLOT_NAME, "w");
#endif

}
void Pipe::close() {
	
#ifdef WIN32
	_pclose(m_pipe);
#else
	pclose(m_pipe)
#endif
}

bool Pipe::isOpen() {
	return m_pipe == nullptr;
}

void Pipe::flush() {
	if (isOpen()) {
		fflush(m_pipe);
	}
		
}

int Pipe::printToPipe(std::string data) {
	if (isOpen()) {
		fprintf(m_pipe, data.c_str());         // set the terminal
		return 1;
	}
	else {
		return 0;
	}
}

int Pipe::printToPipe(std::string data, std::string dane = "") {
	if (isOpen()) {
		if (dane != "")
			fprintf(m_pipe, data.c_str());         // set the terminal
		else
			fprintf(m_pipe, data.c_str(), dane);
		return 1;
	}
	else {
		return 0;
	}
}


int Pipe::printToPipe(std::string data, double dane) {

	if (isOpen()) {
		fprintf(m_pipe, "%d\n", dane);         // set the terminal
		return 1;
	}
	else {
		return 0;
	}

}
