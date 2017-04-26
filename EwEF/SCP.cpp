#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "SCP.h"



int SCP::numberOfActiveObjs = 0;

bool SCP::readScpFile(std::string filePath)
{

	std::ifstream plik(filePath);

	if (!plik.is_open()) {
		fprintf(stderr, "Could not load file %s\n", filePath.c_str());
		return false;
	}
	else {
		std::string tmp;
		bool okay = true;
		std::getline(plik, tmp);
		if (tmp.find("SCP") == std::string::npos) {
			fprintf(stderr, "File format is unsupported! Only Oscilloscope data accepted!\n");
			return false;
		}
		std::getline(plik, tmp);//get rid of first blank line
		//get time info
		while (std::getline(plik, tmp)) {
			
			if (tmp.find("---") != std::string::npos)
			{
				break;
			}
			else {
				if (tmp.size() > 0) {
					m_header.push_back(tmp);
				}
			}
		}
		double time, chA, chB;
		while (plik >> time >> chA >> chB ) {
			m_time.push_back(time);
			m_channelA.push_back(chA);
			m_channelB.push_back(chB);
		}
		decodeHeader();
		m_fileName = getFileName(filePath);
		return true;
	}
}

void SCP::printTime()
{
	for (unsigned int i = 0; i < m_time.size(); i++) {
		std::cout << m_time[i] << std::endl;
	}
}

void SCP::saveFile()
{
	std::ofstream plik("dane_obrobione" + m_fileName);
	for (unsigned int i = 0; i < m_time.size(); i++) {
		plik << m_time[i] << " " << m_channelA[i] << " " << m_channelB[i] <<std::endl;
	}
}

void SCP::printHeader()
{
	for (auto &it : m_headerDecodedDbls) {
		std::cout << it << std::endl;
	}
	for (auto &it : m_columnDesc) {
		std::cout << it << std::endl;
	}
}

void SCP::printChA()
{
	for (unsigned int i = 0; i < m_channelA.size(); i++) {
		std::cout << m_channelA[i] << std::endl;
	}
}

void SCP::decodeHeader()
{
	std::stringstream ss;
	std::string trash, need1, need2;
	double val;

	ss << m_header[0];//time base
	ss >> trash >> trash >> val;
	m_headerDecodedDbls.push_back(val);
	ss = std::stringstream();

	ss << m_header[1];//time offset
	ss >> trash >> trash >> val;
	m_headerDecodedDbls.push_back(val);
	ss = std::stringstream();

	ss << m_header[2];//CHA sensitivity 
	ss >> trash >> trash >> trash >> trash >> val;
	m_headerDecodedDbls.push_back(val);
	ss = std::stringstream();

	ss << m_header[3];//CHA offset
	ss >> trash >> trash >> trash >> val;
	m_headerDecodedDbls.push_back(val);
	ss = std::stringstream();

	ss << m_header[4];//CHA color
	ss >> trash >> trash >> trash >> val;
	m_headerDecodedDbls.push_back(val);
	ss=std::stringstream();

	ss << m_header[5];//CHA sensitivity 
	ss >> trash >> trash >> trash >> trash >> val;
	m_headerDecodedDbls.push_back(val);
	ss = std::stringstream();

	ss << m_header[6];//CHA offset
	ss >> trash >> trash >> trash >> val;
	m_headerDecodedDbls.push_back(val);
	ss = std::stringstream();

	ss << m_header[7];//CHA color
	ss >> trash >> trash >> trash >> val;
	m_headerDecodedDbls.push_back(val);
	ss = std::stringstream();

	ss << m_header[10];//col1
	ss >> trash >> val >> need1 >> need2;
	m_columnDesc.push_back(need1 + " " + need2);
	ss = std::stringstream();

	ss << m_header[11];//col1
	ss >> trash >> val >> need1 >> need2;
	m_columnDesc.push_back(need1 + " " + need2);
	ss = std::stringstream();

	ss << m_header[12];//col1
	ss >> trash >> val >> need1 >> need2;
	m_columnDesc.push_back(need1 + " " + need2);
	ss = std::stringstream();

}

void SCP::printChB()
{
	for (unsigned int i = 0; i < m_channelB.size(); i++) {
		std::cout << m_channelB[i] << std::endl;
	}
}

SCP::SCP()
{
	numberOfActiveObjs++;
}


SCP::~SCP()
{
	numberOfActiveObjs--;
}
