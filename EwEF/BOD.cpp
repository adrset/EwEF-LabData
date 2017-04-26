#include "BOD.h"

#include <fstream>
#include <iostream>
#include <sstream>

BOD::BOD()
{
	numberOfActiveObjs++;
}




BOD::~BOD()
{
	numberOfActiveObjs--;
}

bool BOD::readBodFile(std::string filePath)
{
	std::ifstream plik(filePath);

	if (!plik.is_open()) {
		fprintf(stderr, "Could not load file %s\n", filePath.c_str() );
		return false;
	}
	else {
		std::string tmp;
		bool okay = true;
		std::getline(plik, tmp);
		if (tmp.find("BOD") == std::string::npos) {
			fprintf(stderr, "File format is unsupported! Only Bode data accepted!\n");
			return false;
		}
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
		double f, g_db, g_lin, phase_deg;
		while (plik >> f >> g_db >> g_lin >> phase_deg) {
			m_freq.push_back(f);
			m_gainDb.push_back(g_db);
			m_gainLinear.push_back(g_lin);
			m_phaseDeg.push_back(phase_deg);
		}
		decodeHeader();
		m_fileName = getFileName(filePath);
		return true;
	}
}

void BOD::decodeHeader()
{
	std::stringstream ss;
	std::string trash, need1, need2;
	double val;

	ss << m_header[0];//c1
	ss >> trash >> trash >> need1 >> need2;
	m_columnDesc.push_back(need1 + " " + need2);
	ss = std::stringstream();

	ss << m_header[1];//c2
	ss >> trash >> trash >> need1 >> need2;
	m_columnDesc.push_back(need1 + " " + need2);
	ss = std::stringstream();

	ss << m_header[2];//c3
	ss >> trash >> trash >> need1 >> need2;
	m_columnDesc.push_back(need1 + " " + need2);
	ss = std::stringstream();

	ss << m_header[3];//c4
	ss >> trash >> trash >> need1 >> need2;
	m_columnDesc.push_back(need1 + " " + need2);
	ss = std::stringstream();

	ss << m_header[4];//trace name
	ss >> trash >> trash >> need1 >> need2;
	m_columnDesc.push_back(need1 + " " + need2);
	ss = std::stringstream();

	ss << m_header[5];//color
	ss >> trash >> val;
	m_headerDecodedDbls.push_back(val);
	ss = std::stringstream();

	ss << m_header[6];//gain range start
	ss >> trash >> val;
	m_headerDecodedDbls.push_back(val);
	ss = std::stringstream();

	ss << m_header[7];//gain range end
	ss >> trash >> val;
	m_headerDecodedDbls.push_back(val);
	ss = std::stringstream();

	ss << m_header[8];//phase range start
	ss >> trash >> val;
	m_headerDecodedDbls.push_back(val);
	ss = std::stringstream();

	ss << m_header[9];//phase range end
	ss >> trash >> val;
	m_headerDecodedDbls.push_back(val);
	ss = std::stringstream();

}

int BOD::numberOfActiveObjs = 0;

void BOD::printHeader()
{

	for (auto &it : m_headerDecodedDbls) {
		std::cout << it << std::endl;
	}
	for (auto &it : m_columnDesc) {
		std::cout << it << std::endl;
	}
}

void BOD::saveFile()
{
	std::ofstream plik("dane_obrobione" + m_fileName);
	plik << m_columnDesc[0] << " " << m_columnDesc[1] << " " << m_columnDesc[2] << " " << m_columnDesc[3] <<std::endl;
	for (unsigned int i = 0; i < m_freq.size(); i++) {
		plik << m_freq[i] << " " << m_gainDb[i] << " " << m_gainLinear[i] << " " << m_phaseDeg[i] << std::endl;
	}

}

void BOD::printFreq()
{
	for (unsigned int i = 0; i < m_freq.size(); i++) {
		std::cout << m_freq[i] << std::endl;
	}
}

void BOD::printGainDb()
{
	for (unsigned int i = 0; i < m_gainDb.size(); i++) {
		std::cout << m_gainDb[i] << std::endl;
	}
}

void BOD::printGainLin()
{
	for (unsigned int i = 0; i < m_gainLinear.size(); i++) {
		std::cout << m_gainLinear[i] << std::endl;
	}
}

void BOD::printPhase()
{
	for (unsigned int i = 0; i < m_phaseDeg.size(); i++) {
		std::cout << m_phaseDeg[i] << std::endl;
	}
}
