#pragma once
#include <string>
#include <vector>
#include "Misc.h"

class SCP
{
public:
	static int numberOfActiveObjs;
	bool readScpFile(std::string filePath);
	void printTime();
	void saveFile();
	void printHeader();
	void printChA();
	void decodeHeader();
	void printChB();
	SCP();
	~SCP();
private:
	std::string m_fileName = "";
	std::vector <double> m_headerDecodedDbls;
	std::vector <std::string> m_columnDesc;
	std::vector <std::string> m_header;
	std::vector < double > m_time;
	std::vector < double > m_channelA;
	std::vector < double > m_channelB;

};

