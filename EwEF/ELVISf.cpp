#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "ELVISf.h"



bool ELVISf::readElvisFile(std::string filePath)
{
	std::ifstream plik(filePath);

	if (!plik.is_open()) {
		fprintf(stderr, "Could not load file %s\n", filePath.c_str());
		return false;
	}
	else {
		std::string tmp, tmp1;
		std::getline(plik, tmp);//holds date and time -> useless
		
		std::getline(plik, tmp, ':');
		std::getline(plik, tmp);
	
		std::replace(tmp.begin(), tmp.end(), ',', '.');
		
		m_amplitude = std::stod(tmp);

		plik >> tmp >> tmp1;
		tmp = tmp + " " + tmp1;
		m_col.push_back(tmp);

		plik >> tmp >> tmp1;
		tmp = tmp + " " + tmp1;
		m_col.push_back(tmp);

		plik >> tmp >> tmp1;
		tmp = tmp + " " + tmp1;
		m_col.push_back(tmp);
		std::stringstream ss;
		double f, g, p;
		std::getline(plik, tmp);
		while (std::getline(plik, tmp)) {
			std::replace(tmp.begin(), tmp.end(), ',', '.');
			ss << tmp;
			ss >> f >> g >> p;
			m_freq.push_back(f);
			m_gain.push_back(g);
			m_phase.push_back(p);
			ss = std::stringstream();
		}
		m_fileName = getFileName(filePath);
		return true;
	}
}

void ELVISf::printAll()
{
	std::cout << "Amplituda: " << m_amplitude << " V" << std::endl;
	for (unsigned int i = 0; i < m_freq.size(); i++) {
		std::cout << m_freq[i] << " " << m_gain[i] << " " << m_phase[i] << std::endl;
	}
}

void ELVISf::saveFile()
{
	std::ofstream plik("dane_obrobione" + m_fileName);
	plik << "#Amplituda: " << m_amplitude << " V" << std::endl;
	for (unsigned int i = 0; i < m_freq.size(); i++) {
		plik << m_freq[i] << " " << m_gain[i] << " " << m_phase[i] << std::endl;
	}
}

ELVISf::ELVISf()
{
}


ELVISf::~ELVISf()
{
}
