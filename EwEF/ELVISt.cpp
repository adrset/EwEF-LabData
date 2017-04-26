#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include "ELVISt.h"


bool ELVISt::readElvisFile(std::string filePath)
{

	std::ifstream plik(filePath);

	if (!plik.is_open()) {
		fprintf(stderr, "Could not load file %s\n", filePath.c_str());
		return false;
	}
	else {
		std::string tmp, a, b ,c , d, e, f;
		double b1, e1, c1, f1;
		bool okay = true; //dane\pr\2\2-t-105Hz-pr.txt
		std::getline(plik, tmp);
		std::getline(plik, tmp);
		std::getline(plik, tmp);
		std::getline(plik, tmp);
		std::getline(plik, tmp);//all lines of text useless
		std::stringstream ss;
		for (;std::getline(plik, tmp);) {//
			
			ss << tmp;
			ss >> a >> b >> c >> d >> e >> f;
			ss = std::stringstream();

			ss << b;
			std::getline(ss, b, ',');
			std::getline(ss, b, ',');
			ss = std::stringstream();

			ss << e;
			std::getline(ss, e, ',');
			std::getline(ss, e, ',');
			b1 = std::stod(b) / 1000000.0;
			e1 = std::stod(e) / 1000000.0;

			std::replace(c.begin(), c.end(), ',', '.');
			std::replace(f.begin(), f.end(), ',', '.');

			c1 = std::stod(c);
			f1 = std::stod(f);
			m_chTimeA.push_back(b1);
			m_chTimeB.push_back(e1);
			m_chValueA.push_back(c1);
			m_chValueB.push_back(f1);
			ss = std::stringstream();
		}
		m_fileName = getFileName(filePath);
		return true;
	}
}

void ELVISt::printAll()
{
	for (unsigned int i = 0; i < m_chTimeA.size(); i++) {
		std::cout << m_chTimeA[i] << " " << m_chValueA[i] << " | " << m_chTimeB[i] << " " << m_chValueB[i] << std::endl;
	}
}

void ELVISt::saveFile()
{
	std::ofstream plik("dane_obrobione" + m_fileName);
	for (unsigned int i = 0; i < m_chTimeA.size(); i++) {
		plik << m_chTimeA[i] << " " << m_chValueA[i] << " " << m_chTimeB[i] << " " << m_chValueB[i] << std::endl;
	}
}

ELVISt::ELVISt()
{
}


ELVISt::~ELVISt()
{
}
