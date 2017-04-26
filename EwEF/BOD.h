#pragma once
#include <string>
#include <vector>
#include "Misc.h"
class BOD
{
public:
	static int numberOfActiveObjs;
	bool readBodFile(std::string filePath);
	void decodeHeader();
	void printHeader();
	void saveFile();
	void printFreq();
	void printGainDb();
	void printGainLin();
	void printPhase();
	BOD();
	~BOD();
private:
	std::string m_fileName="";
	std::vector< double > m_freq;
	std::vector< double > m_gainDb;
	std::vector< double > m_gainLinear;
	std::vector< double > m_phaseDeg;
	std::vector< std::string > m_header;
	std::vector <std::string> m_columnDesc;
	std::vector <double> m_headerDecodedDbls;
	char color;
};

