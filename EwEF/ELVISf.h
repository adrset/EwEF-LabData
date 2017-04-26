#pragma once
#include <string>
#include <vector>
#include "Misc.h"

class ELVISf
{
public:
	bool readElvisFile(std::string filePath);
	void printAll();
	void saveFile();
	ELVISf();
	~ELVISf();
private:
	std::string m_fileName = "";
	double m_amplitude;
	std::vector<double> m_freq;
	std::vector<double> m_gain;
	std::vector<double> m_phase;
	std::vector<std::string> m_col;
};

