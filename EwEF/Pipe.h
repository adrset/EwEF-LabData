#pragma once
#include <cstdio>
#include <string>

#ifdef WIN32
#define GNUPLOT_NAME "gnuplot"
#else 
#define GNUPLOT_NAME "gnuplot"
#endif

class Pipe
{
public:
	void init();
	void close();
	void flush();
	Pipe();
	virtual ~Pipe();
	bool isOpen() ;
	int printToPipe(std::string data);
	int printToPipe(std::string data, double dane);
	int printToPipe(std::string data, std::string dane);
private:
	FILE *m_pipe;
};

